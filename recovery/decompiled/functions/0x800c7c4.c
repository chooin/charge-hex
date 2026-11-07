// rea decompile_all
// name: fw_0800c7c4
// address: 0x800c7c4
// body: available
// range: 0x800c7c4-0x800c80f inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


void fw_0800c7c4(undefined1 param_1,uint param_2,undefined1 param_3,int param_4,undefined1 param_5)

{
  uint uVar1;
  
  if (param_2 < 0xa7) {
    DAT_20000a18 = param_5;
    DAT_20000a19 = (char)param_2 + '\x03';
    DAT_20000a1a = param_1;
    DAT_20000a1b = param_3;
    for (uVar1 = 0; uVar1 < param_2; uVar1 = uVar1 + 1 & 0xff) {
      *(undefined1 *)(uVar1 + 0x20000a1c) = *(undefined1 *)(param_4 + uVar1);
    }
    *(undefined1 *)(param_2 + 0x20000a1c) = 0;
    for (uVar1 = 1; uVar1 < param_2 + 4; uVar1 = uVar1 + 1 & 0xff) {
      *(byte *)(param_2 + 0x20000a1c) = *(byte *)(param_2 + 0x20000a1c) ^ (&DAT_20000a18)[uVar1];
    }
    fw_0800947c(&DAT_20000a18,param_2 + 5);
  }
  return;
}

