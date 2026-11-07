// rea decompile_all
// name: fw_080047d4
// address: 0x80047d4
// body: available
// range: 0x80047d4-0x800491b inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


void fw_080047d4(undefined4 param_1,uint param_2,uint param_3)

{
  uint uVar1;
  byte bVar2;
  uint local_28;
  
  local_28 = 0x81;
  uVar1 = ~(param_2 + 0x81 + param_3 + (param_3 >> 8) + (param_3 >> 0x10)) & 0xff;
  fw_0800462c(param_1);
  fw_08004600(0x14);
  bVar2 = 0;
  do {
    fw_08005d46(0x48000800,0x2000);
    fw_08005d46(0x48000800,0x8000,(int)(local_28 << 0x18) < 0);
    local_28 = (local_28 & 0x7f) << 1;
    fw_08004600(0x50);
    fw_08005d46(0x48000800,0x2000,0);
    fw_08004600(0x50);
    bVar2 = bVar2 + 1;
  } while (bVar2 < 8);
  bVar2 = 0;
  do {
    fw_08005d46(0x48000800,0x2000);
    fw_08005d46(0x48000800,0x8000,(int)(param_2 << 0x18) < 0);
    param_2 = (param_2 & 0x7f) << 1;
    fw_08004600(0x50);
    fw_08005d46(0x48000800,0x2000,0);
    fw_08004600(0x50);
    bVar2 = bVar2 + 1;
  } while (bVar2 < 8);
  bVar2 = 0;
  do {
    fw_08005d46(0x48000800,0x2000,1);
    fw_08005d46(0x48000800,0x8000,(int)(param_3 << 8) < 0);
    param_3 = param_3 << 1;
    fw_08004600(0x50);
    fw_08005d46(0x48000800,0x2000,0);
    fw_08004600(0x50);
    bVar2 = bVar2 + 1;
  } while (bVar2 < 0x18);
  bVar2 = 0;
  do {
    fw_08005d46(0x48000800,0x2000,1);
    fw_08005d46(0x48000800,0x8000,(int)(uVar1 << 0x18) < 0);
    uVar1 = (uVar1 & 0x7f) << 1;
    fw_08004600(0x50);
    fw_08005d46(0x48000800,0x2000,0);
    fw_08004600(0x50);
    bVar2 = bVar2 + 1;
  } while (bVar2 < 8);
  fw_0800460a(param_1);
  return;
}

