// rea decompile_all
// name: fw_0800c20c
// address: 0x800c20c
// body: available
// range: 0x800c20c-0x800c27d inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_0800c20c(byte *param_1)

{
  int iVar1;
  
  if (param_1 != (byte *)0x0) {
    if (_DAT_200000c8 == CONCAT31(CONCAT21(CONCAT11(param_1[1],param_1[2]),param_1[3]),param_1[4]))
    {
      _DAT_200000c8 = _DAT_200000c8 + 1;
      DAT_200000be = 0;
      DAT_200000bf = 0;
      _DAT_200008de = 0;
      iVar1 = (*param_1 - 1 & 0xff) * 0x34;
      if (*(short *)(iVar1 + 0x2000060e) == 1) {
        if (_DAT_20000890 < *(ushort *)(iVar1 + 0x200005f2)) {
          _DAT_20000890 = 0;
        }
        else {
          _DAT_20000890 = _DAT_20000890 - *(ushort *)(iVar1 + 0x200005f2);
        }
        _DAT_20000894 = _DAT_2000088c + _DAT_20000890;
        *(undefined2 *)(iVar1 + 0x2000060e) = 0;
        *(undefined4 *)(iVar1 + 0x20000604) = 0;
        *(undefined2 *)(iVar1 + 0x200005f2) = 0;
        *(undefined1 *)(iVar1 + 0x20000614) = 0;
        *(undefined1 *)(iVar1 + 0x20000612) = 1;
      }
    }
  }
  return;
}

