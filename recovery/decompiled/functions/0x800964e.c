// rea decompile_all
// name: fw_0800964e
// address: 0x800964e
// body: available
// range: 0x800964e-0x8009693 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


void fw_0800964e(undefined4 *param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  undefined4 local_c;
  char local_8;
  undefined1 local_7 [3];
  
  if ((param_1 != (undefined4 *)0x0) && (param_2 != (char *)0x0)) {
    local_c = *param_1;
    if (*param_2 == 'U') {
      uVar1 = 0;
    }
    else {
      if (*param_2 != 'f') {
        return;
      }
      uVar1 = 1;
    }
    local_7._1_2_ = (undefined2)((uint)param_4 >> 0x10);
    _local_8 = CONCAT31(CONCAT21(local_7._1_2_,uVar1),param_2[2]);
    fw_0800c7c4(0x10,6,1,&local_c,0xaa);
  }
  return;
}

