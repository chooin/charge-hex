// rea decompile_all
// name: fw_08008614
// address: 0x8008614
// body: available
// range: 0x8008614-0x80086a3 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_08008614(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int extraout_r1;
  undefined4 extraout_r1_00;
  
  iVar1 = fw_08005d3c(0x48000400,0x1000,param_3,param_4,param_4);
  if (iVar1 == 0) {
    fw_0800cc44(5);
    iVar1 = fw_08005d3c(0x48000400,0x1000);
    if (iVar1 == 0) {
      if ((((DAT_20000854 == '\x01') || (DAT_20000854 == '\x03')) || (DAT_20000854 == '\x04')) ||
         (DAT_20000854 == '\x05')) {
        DAT_20000854 = '\x02';
      }
      else if (DAT_20000854 != '\x02') {
        return;
      }
      fw_0800cdb8(0xc);
      if (_DAT_200008da != 0) {
        _DAT_20000882 = 0;
        _DAT_20000886 = 0;
        _DAT_20000884 = 0;
        _DAT_2000089c = 0;
        _DAT_20000888 = 0;
        _DAT_200008da = 0;
      }
      _DAT_20000882 = _DAT_20000882 + 1;
      fw_080040e8(_DAT_2000088c + 10,1000000);
      _DAT_2000088c = extraout_r1;
      fw_080040e8(extraout_r1 + _DAT_20000890,1000000);
      _DAT_20000894 = extraout_r1_00;
      fw_0800a4b4(&DAT_0800fc2c,extraout_r1);
      _DAT_200008d6 = 10;
    }
  }
  return;
}

