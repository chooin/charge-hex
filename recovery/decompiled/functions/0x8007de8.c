// rea decompile_all
// name: fw_08007de8
// address: 0x8007de8
// body: available
// range: 0x8007de8-0x8007f11 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_08007de8(void)

{
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined1 auStack_20 [4];
  uint local_1c;
  
  fw_080041cc(&local_30,0x14);
  _DAT_40021014 = _DAT_40021014 | 0x4e0000;
  local_1c = _DAT_40021014 & 0x40000;
  fw_08005d46(0x48000800,0xa000,0);
  fw_08005d46(0x48000000,0x9011,0);
  fw_08005d46(0x48000400,0xee10,1);
  fw_08005d46(0x48000000,0x100);
  fw_08005d46(0x48000400,0x128,0);
  local_30 = 0xa000;
  local_2c = 1;
  local_28 = 0;
  local_24 = 0;
  fw_08005bcc(0x48000800,&local_30);
  local_30 = 0x4000;
  local_2c = 0;
  local_28 = 0;
  fw_08005bcc(0x48000800,&local_30);
  local_30 = 0x9111;
  local_24 = 3;
  local_2c = 1;
  local_28 = 0;
  fw_08005bcc(0x48000000,&local_30);
  local_30 = 0x8e2;
  local_2c = 0;
  local_28 = 0;
  fw_08005bcc(0x48000000,&local_30);
  local_30 = 5;
  local_2c = 0;
  local_28 = 0;
  fw_08005bcc(0x48000400,&local_30);
  local_30 = 0x8f28;
  local_24 = 3;
  local_2c = 1;
  local_28 = 0;
  fw_08005bcc(0x48000400,&local_30);
  local_30 = 0x1000;
  local_2c = 0x10210000;
  local_28 = 0;
  fw_08005bcc(0x48000400,&local_30);
  local_30 = 0x6010;
  local_2c = 0x11;
  local_28 = 0;
  local_24 = 3;
  fw_08005bcc(0x48000400,&local_30,auStack_20);
  fw_080063e4(7,0);
  fw_080063cc(7);
  return;
}

