// rea decompile_all
// name: fw_080041e2
// address: 0x80041e2
// body: available
// range: 0x80041e2-0x800425b inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


uint fw_080041e2(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  if (((param_1 & 0x7fffffff) != 0) && ((param_2 & 0x7fffffff) != 0)) {
    iVar3 = ((param_1 & 0x7fffffff) >> 0x17) + ((param_2 & 0x7fffffff) >> 0x17);
    uVar1 = param_1 & 0x7fffff;
    uVar5 = param_2 & 0x7fffff;
    uVar2 = uVar5 * uVar1 + (uVar1 + uVar5) * 0x800000 >> 0x10;
    uVar6 = ((~uVar2 + (uVar5 >> 8) * (uVar1 >> 8) + (uVar1 + uVar5) * 0x80 >> 0x10) + 0x4001) *
            0x10000;
    iVar4 = iVar3 + -0x7f;
    if ((uVar5 * uVar1 & 0xffff) != 0) {
      uVar6 = uVar6 + 1;
    }
    uVar2 = uVar2 | uVar6;
    if (-1 < (int)uVar2) {
      uVar2 = uVar2 << 1;
      iVar4 = iVar3 + -0x80;
    }
    uVar1 = iVar4 * 0x1000000 + (uVar2 >> 7) + 1;
    uVar5 = uVar1 >> 1;
    if ((uVar2 & 0xff) == 0x80) {
      uVar5 = (uVar1 >> 2) << 1;
    }
    if (iVar4 < 0) {
      uVar5 = 0;
    }
    return uVar5 | (param_1 ^ param_2) & 0x80000000;
  }
  return 0;
}

