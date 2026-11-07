// rea decompile_all
// name: fw_08000582
// address: 0x8000582
// body: available
// range: 0x8000582-0x800061d inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


void fw_08000582(undefined4 *param_1)

{
  uint *puVar1;
  code *UNRECOVERED_JUMPTABLE;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar3 = *(uint *)param_1[0xf];
  puVar1 = (uint *)*param_1;
  uVar2 = *puVar1;
  uVar4 = param_1[0x10];
  if (((4 << (uVar4 & 0xff) & uVar3) == 0) || (-1 < (int)(uVar2 << 0x1d))) {
    if (((2 << (uVar4 & 0xff) & uVar3) == 0) || (-1 < (int)(uVar2 << 0x1e))) {
      if ((8 << (uVar4 & 0xff) & uVar3) == 0) {
        return;
      }
      if (-1 < (int)(uVar2 << 0x1c)) {
        return;
      }
      *puVar1 = *puVar1 & 0xfffffff1;
      *(int *)(param_1[0xf] + 4) = 1 << (param_1[0x10] & 0xff);
      param_1[0xe] = 1;
      *(undefined1 *)((int)param_1 + 0x21) = 1;
      *(undefined1 *)(param_1 + 8) = 0;
      UNRECOVERED_JUMPTABLE = (code *)param_1[0xc];
    }
    else {
      if (-1 < (int)(*puVar1 << 0x1a)) {
        *puVar1 = *puVar1 & 0xfffffff5;
        *(undefined1 *)((int)param_1 + 0x21) = 1;
      }
      *(int *)(param_1[0xf] + 4) = 2 << (param_1[0x10] & 0xff);
      *(undefined1 *)(param_1 + 8) = 0;
      UNRECOVERED_JUMPTABLE = (code *)param_1[10];
    }
  }
  else {
    if (-1 < (int)(*puVar1 << 0x1a)) {
      *puVar1 = *puVar1 & 0xfffffffb;
    }
    *(int *)(param_1[0xf] + 4) = 4 << (param_1[0x10] & 0xff);
    UNRECOVERED_JUMPTABLE = (code *)param_1[0xb];
  }
  if (UNRECOVERED_JUMPTABLE == (code *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x080005ee. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}

