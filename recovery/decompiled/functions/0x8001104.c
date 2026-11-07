// rea decompile_all
// name: fw_08001104
// address: 0x8001104
// body: available
// range: 0x8001104-0x80011dd inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 fw_08001104(byte *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  
  if (*(int *)param_1 << 0xf < 0) {
    bVar5 = -1 < (int)(_DAT_4002101c << 3);
    if (bVar5) {
      _DAT_4002101c = _DAT_4002101c | 0x10000000;
    }
    if (-1 < (int)(_DAT_40007000 << 0x17)) {
      _DAT_40007000 = _DAT_40007000 | 0x100;
      iVar2 = fw_08000a88();
      while (-1 < (int)(_DAT_40007000 << 0x17)) {
        iVar4 = fw_08000a88();
        if (100 < (uint)(iVar4 - iVar2)) {
          return 3;
        }
      }
    }
    if ((((_DAT_40021020 & 0x300) != 0) &&
        ((*(uint *)(param_1 + 4) & 0x300) != (_DAT_40021020 & 0x300))) &&
       (uVar3 = _DAT_40021020 & 0xfffffcff, uVar1 = _DAT_40021020 & 1, _DAT_40021020 = uVar3,
       uVar1 != 0)) {
      iVar2 = fw_08000a88();
      while (-1 < (int)(_DAT_40021020 << 0x1e)) {
        iVar4 = fw_08000a88();
        if (5000 < (uint)(iVar4 - iVar2)) {
          return 3;
        }
      }
    }
    _DAT_40021020 = _DAT_40021020 & 0xfffffcff | *(uint *)(param_1 + 4);
    if (bVar5) {
      _DAT_4002101c = _DAT_4002101c & 0xefffffff;
    }
  }
  if ((*param_1 & 1) != 0) {
    _DAT_40021030 = _DAT_40021030 & 0xfffffffc | *(uint *)(param_1 + 8);
  }
  if ((int)((uint)*param_1 << 0x1a) < 0) {
    _DAT_40021030 = _DAT_40021030 & 0xffffffef | *(uint *)(param_1 + 0xc);
  }
  return 0;
}

