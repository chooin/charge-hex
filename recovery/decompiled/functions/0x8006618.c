// rea decompile_all
// name: fw_08006618
// address: 0x8006618
// body: available
// range: 0x8006618-0x800666b inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_08006618(void)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  byte local_28 [32];
  
  local_28[0] = 2;
  local_28[1] = 3;
  local_28[2] = 4;
  local_28[3] = 5;
  local_28[4] = 6;
  local_28[5] = 7;
  local_28[6] = 8;
  local_28[7] = 9;
  local_28[8] = 10;
  local_28[9] = 0xb;
  local_28[10] = 0xc;
  local_28[0xb] = 0xd;
  local_28[0xc] = 0xe;
  local_28[0xd] = 0xf;
  local_28[0xe] = 0x10;
  local_28[0xf] = 0x10;
  local_28[0x10] = 1;
  local_28[0x11] = 2;
  local_28[0x12] = 3;
  local_28[0x13] = 4;
  local_28[0x14] = 5;
  local_28[0x15] = 6;
  local_28[0x16] = 7;
  local_28[0x17] = 8;
  local_28[0x18] = 9;
  local_28[0x19] = 10;
  local_28[0x1a] = 0xb;
  local_28[0x1b] = 0xc;
  local_28[0x1c] = 0xd;
  local_28[0x1d] = 0xe;
  local_28[0x1e] = 0xf;
  local_28[0x1f] = 0x10;
  if (((_DAT_40021004 & 0xc) != 4) && ((_DAT_40021004 & 0xc) == 8)) {
    bVar1 = local_28[(_DAT_40021004 & 0x3fffff) >> 0x12];
    if ((int)(_DAT_40021004 << 0xf) < 0) {
      uVar2 = fw_0800413c(8000000,0,local_28[(_DAT_4002102c & 0xf) + 0x10]);
      uVar3 = (uint)bVar1;
    }
    else {
      uVar3 = 4000000;
      uVar2 = (uint)bVar1;
    }
    fw_080095a2(uVar2,uVar3);
  }
  return;
}

