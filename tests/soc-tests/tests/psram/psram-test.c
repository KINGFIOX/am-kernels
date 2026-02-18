/*
 * PSRAM Read/Write Test
 *
 * This test verifies the QSPI PSRAM functionality by:
 * 1. Writing data to PSRAM
 * 2. Reading back and verifying the data
 * 3. Testing various access patterns (byte, half-word, word)
 * 4. Testing boundary conditions
 *
 * PSRAM uses QSPI protocol:
 * - Read command: 0xEB (Quad I/O Fast Read)
 * - Write command: 0x38 (Quad Page Program)
 */

#include "trap.h"

#define UNUSED __attribute__((unused))

/* PSRAM_BASE and PSRAM_SIZE are defined via CFLAGS from NPC_HOME/.config */
#ifndef PSRAM_BASE
#error "PSRAM_BASE not defined. Please build with ARCH=riscv32-npc"
#endif

#ifndef PSRAM_SIZE
#error "PSRAM_SIZE not defined. Please build with ARCH=riscv32-npc"
#endif

/* Test patterns */
#define PATTERN_WORD    0xDEADBEEF
#define PATTERN_HALF    0xCAFE
#define PATTERN_BYTE    0x42
#define PATTERN_WALK1   0xAAAAAAAA
#define PATTERN_WALK0   0x55555555

/* Test area size (avoid testing entire PSRAM for speed) */
#define TEST_AREA_SIZE  0x1000  /* 4KB for quick test */

static int test_count = 0;
static int pass_count = 0;

static void test_result(const char *name, bool passed) {
  test_count++;
  if (passed) {
    pass_count++;
    printf("[PASS] %s\n", name);
  } else {
    printf("[FAIL] %s\n", name);
  }
}

UNUSED
/* Test 1: Basic word read/write */
static bool test_word_access(void) {
  volatile uint32_t *psram = (volatile uint32_t *)PSRAM_BASE;
  uint32_t patterns[] = {PATTERN_WORD, PATTERN_WALK1, PATTERN_WALK0, 0x12345678, 0x0};
  bool passed = true;

  for (int i = 0; i < sizeof(patterns) / sizeof(patterns[0]); i++) {
    psram[i] = patterns[i];
  }

  for (int i = 0; i < sizeof(patterns) / sizeof(patterns[0]); i++) {
    uint32_t read_val = psram[i];
    if (read_val != patterns[i]) {
      printf("  Word[%d]: expected 0x%08x, got 0x%08x\n", i, patterns[i], read_val);
      passed = false;
    }
  }

  return passed;
}

UNUSED
/* Test 2: Half-word read/write */
static bool test_halfword_access(void) {
  volatile uint16_t *psram = (volatile uint16_t *)(PSRAM_BASE + 0x100);
  uint16_t patterns[] = {PATTERN_HALF, 0x1234, 0xABCD, 0x5A5A, 0xA5A5};
  bool passed = true;

  for (int i = 0; i < sizeof(patterns) / sizeof(patterns[0]); i++) {
    psram[i] = patterns[i];
  }

  for (int i = 0; i < sizeof(patterns) / sizeof(patterns[0]); i++) {
    uint16_t read_val = psram[i];
    if (read_val != patterns[i]) {
      printf("  Half[%d]: expected 0x%04x, got 0x%04x\n", i, patterns[i], read_val);
      passed = false;
    }
  }

  return passed;
}

UNUSED
/* Test 3: Byte read/write */
static bool test_byte_access(void) {
  volatile uint8_t *psram = (volatile uint8_t *)(PSRAM_BASE + 0x200);
  bool passed = true;

  /* Write bytes 0-255 */
  for (int i = 0; i < 256; i++) {
    psram[i] = (uint8_t)i;
  }

  /* Read back and verify */
  for (int i = 0; i < 256; i++) {
    uint8_t read_val = psram[i];
    if (read_val != (uint8_t)i) {
      printf("  Byte[%d]: expected 0x%02x, got 0x%02x\n", i, (uint8_t)i, read_val);
      passed = false;
    }
  }

  return passed;
}

UNUSED
/* Test 4: Sequential write then read (burst-like) */
static bool test_sequential_access(void) {
  volatile uint32_t *psram = (volatile uint32_t *)(PSRAM_BASE + 0x400);
  int count = 64;  /* 64 words = 256 bytes */
  bool passed = true;

  /* Write sequential pattern */
  for (int i = 0; i < count; i++) {
    psram[i] = i * 0x01010101;
  }

  /* Read back and verify */
  for (int i = 0; i < count; i++) {
    uint32_t expected = i * 0x01010101;
    uint32_t read_val = psram[i];
    if (read_val != expected) {
      printf("  Seq[%d]: expected 0x%08x, got 0x%08x\n", i, expected, read_val);
      passed = false;
      if (i > 5) {
        printf("  ... (more errors)\n");
        break;
      }
    }
  }

  return passed;
}

UNUSED
/* Test 5: Address line test (check for address shorts) */
static bool test_address_lines(void) {
  volatile uint32_t *psram = (volatile uint32_t *)PSRAM_BASE;
  bool passed = true;

  /* Write unique values at power-of-2 offsets */
  uint32_t offsets[] = {0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
  int num_offsets = sizeof(offsets) / sizeof(offsets[0]);

  for (int i = 0; i < num_offsets; i++) {
    if (offsets[i] * 4 < PSRAM_SIZE) {
      psram[offsets[i]] = offsets[i];
    }
  }

  /* Read back and verify */
  for (int i = 0; i < num_offsets; i++) {
    if (offsets[i] * 4 < PSRAM_SIZE) {
      uint32_t read_val = psram[offsets[i]];
      if (read_val != offsets[i]) {
        printf("  Addr[0x%x]: expected 0x%08x, got 0x%08x\n",
               offsets[i] * 4, offsets[i], read_val);
        passed = false;
      }
    }
  }

  return passed;
}

UNUSED
/* Test 6: Read-modify-write */
static bool test_read_modify_write(void) {
  volatile uint32_t *psram = (volatile uint32_t *)(PSRAM_BASE + 0x800);
  bool passed = true;

  /* Initial write */
  psram[0] = 0x00000000;

  /* Read-modify-write operations */
  uint32_t val = psram[0];
  val |= 0x000000FF;
  psram[0] = val;

  val = psram[0];
  val |= 0x0000FF00;
  psram[0] = val;

  val = psram[0];
  val |= 0x00FF0000;
  psram[0] = val;

  val = psram[0];
  val |= 0xFF000000;
  psram[0] = val;

  /* Verify final value */
  uint32_t final_val = psram[0];
  if (final_val != 0xFFFFFFFF) {
    printf("  RMW: expected 0xFFFFFFFF, got 0x%08x\n", final_val);
    passed = false;
  }

  return passed;
}

UNUSED
/* Test 7: Interleaved read/write (tests back-to-back transactions) */
static bool test_interleaved_rw(void) {
  /* Use middle of PSRAM to avoid conflict with .data and .stack */
  volatile uint32_t *psram = (volatile uint32_t *)(PSRAM_BASE + PSRAM_SIZE / 2);
  bool passed = true;
  int count = 32;

  /* Pattern 1: Write-Read-Write-Read on same address */
  for (int i = 0; i < count; i++) {
    uint32_t pattern = 0x12340000 | i;
    psram[0] = pattern;           /* Write */
    uint32_t read_val = psram[0]; /* Read immediately after */
    if (read_val != pattern) {
      printf("  Interleave1[%d]: expected 0x%08x, got 0x%08x\n", i, pattern, read_val);
      passed = false;
    }
  }

  /* Pattern 2: Write A, Read A, Write B, Read B (alternating addresses) */
  for (int i = 0; i < count; i++) {
    uint32_t patternA = 0xAAAA0000 | i;
    uint32_t patternB = 0xBBBB0000 | i;

    psram[0] = patternA;          /* Write A */
    uint32_t readA = psram[0];    /* Read A */
    psram[1] = patternB;          /* Write B */
    uint32_t readB = psram[1];    /* Read B */

    if (readA != patternA) {
      printf("  Interleave2A[%d]: expected 0x%08x, got 0x%08x\n", i, patternA, readA);
      passed = false;
    }
    if (readB != patternB) {
      printf("  Interleave2B[%d]: expected 0x%08x, got 0x%08x\n", i, patternB, readB);
      passed = false;
    }
  }

  /* Pattern 3: Write multiple, then read-write interleaved */
  for (int i = 0; i < count; i++) {
    psram[i] = (uint32_t)i * 0x11111111U;
  }
  for (int i = 0; i < count; i++) {
    uint32_t expected = (uint32_t)i * 0x11111111U;
    uint32_t read_val = psram[i];       /* Read */
    psram[i] = read_val + 1;            /* Write (modify) */
    uint32_t verify = psram[i];         /* Read again */

    if (read_val != expected) {
      printf("  Interleave3R[%d]: expected 0x%08x, got 0x%08x\n", i, expected, read_val);
      passed = false;
    }
    if (verify != expected + 1) {
      printf("  Interleave3V[%d]: expected 0x%08x, got 0x%08x\n", i, expected + 1, verify);
      passed = false;
    }
  }

  /* Pattern 4: Rapid write-read-write-read sequence (stress test) */
  for (int round = 0; round < 8; round++) {
    for (int i = 0; i < count; i++) {
      uint32_t w1 = (round << 24) | (i << 16) | 0x1111;
      uint32_t w2 = (round << 24) | (i << 16) | 0x2222;

      psram[i] = w1;              /* Write 1 */
      uint32_t r1 = psram[i];     /* Read 1 */
      psram[i] = w2;              /* Write 2 */
      uint32_t r2 = psram[i];     /* Read 2 */

      if (r1 != w1 || r2 != w2) {
        printf("  Interleave4[%d,%d]: w1=0x%08x r1=0x%08x w2=0x%08x r2=0x%08x\n",
               round, i, w1, r1, w2, r2);
        passed = false;
        if (i > 3) break;
      }
    }
    if (!passed) break;
  }

  return passed;
}

UNUSED
/* Test 8: Walking ones/zeros */
static bool test_walking_pattern(void) {
  volatile uint32_t *psram = (volatile uint32_t *)(PSRAM_BASE + 0xC00);
  bool passed = true;

  /* Walking ones */
  for (int bit = 0; bit < 32; bit++) {
    uint32_t pattern = 1U << bit;
    psram[bit] = pattern;
  }

  for (int bit = 0; bit < 32; bit++) {
    uint32_t expected = 1U << bit;
    uint32_t read_val = psram[bit];
    if (read_val != expected) {
      printf("  Walk1[%d]: expected 0x%08x, got 0x%08x\n", bit, expected, read_val);
      passed = false;
    }
  }

  /* Walking zeros */
  for (int bit = 0; bit < 32; bit++) {
    uint32_t pattern = ~(1U << bit);
    psram[32 + bit] = pattern;
  }

  for (int bit = 0; bit < 32; bit++) {
    uint32_t expected = ~(1U << bit);
    uint32_t read_val = psram[32 + bit];
    if (read_val != expected) {
      printf("  Walk0[%d]: expected 0x%08x, got 0x%08x\n", bit, expected, read_val);
      passed = false;
    }
  }

  return passed;
}

int main() {
  printf("=== PSRAM Test ===\n");
  printf("PSRAM Base: 0x%08x, Size: 0x%x (%d KB)\n\n",
         PSRAM_BASE, PSRAM_SIZE, PSRAM_SIZE / 1024);

  /* Run all tests */
  test_result("Word Access", test_word_access());
  test_result("Half-word Access", test_halfword_access());
  test_result("Byte Access", test_byte_access());
  test_result("Sequential Access", test_sequential_access());
  test_result("Address Lines", test_address_lines());
  test_result("Read-Modify-Write", test_read_modify_write());
  test_result("Interleaved R/W", test_interleaved_rw());
  test_result("Walking Pattern", test_walking_pattern());

  /* Summary */
  printf("\n=== Test Summary ===\n");
  printf("Passed: %d / %d\n", pass_count, test_count);

  /* Halt with error if any test failed */
  check(pass_count == test_count);

  printf("All PSRAM tests passed!\n");
  return 0;
}
