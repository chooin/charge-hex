// rea decompile_all
// name: fw_0800b960
// address: 0x800b960
// body: available
// range: 0x800b960-0x800ba71 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_0800b960(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  ushort uVar5;
  undefined2 uVar6;
  undefined1 local_dc [168];
  undefined4 local_34;
  uint local_30;
  undefined4 local_2c;
  undefined4 local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  undefined4 local_18;
  
  local_18 = 0x26;
  uVar4 = 1;
  local_dc[0] = 6;
  if (param_1 == 0) {
    uVar3 = 0;
    local_24 = 6;
  }
  else {
    uVar3 = 6;
    local_24 = 0xc;
  }
  do {
    local_1c = uVar3 + 1;
    uVar5 = 0;
    local_20 = local_1c & 0xff;
    local_28 = 0;
    local_2c = 0;
    uVar6 = 0;
    local_30 = 0;
    iVar1 = fw_0800a690(uVar3);
    if (iVar1 == 0) {
      iVar1 = uVar3 * 0x34;
      iVar2 = iVar1 + 0x200005e4;
      if (*(char *)(iVar1 + 0x200005fa) == '\0') {
        local_34 = 1;
      }
      else {
        local_34 = 2;
        uVar5 = *(ushort *)(iVar1 + 0x200005e8);
        local_28 = fw_080040e8(*(undefined4 *)(iVar1 + 0x200005e4),0x3c);
        local_2c = fw_08009f88(uVar3);
        uVar6 = *(undefined2 *)(iVar2 + 0x10);
        local_30 = (uint)*(ushort *)(iVar2 + 0x12);
        if (_DAT_20000872 <= uVar5) {
          *(undefined1 *)(uVar3 + 0x20000ac0) = 1;
        }
      }
    }
    else {
      local_34 = 4;
    }
    local_dc[uVar4] = (char)local_20;
    uVar4 = uVar4 + 1 & 0xff;
    local_dc[uVar4] = 0;
    uVar4 = uVar4 + 1 & 0xff;
    local_dc[uVar4] = (char)local_34;
    uVar4 = uVar4 + 1 & 0xff;
    local_dc[uVar4] = (char)((uint)local_28 >> 8);
    uVar4 = uVar4 + 1 & 0xff;
    local_dc[uVar4] = (char)local_28;
    uVar4 = uVar4 + 1 & 0xff;
    local_dc[uVar4] = (char)(uVar5 >> 8);
    uVar4 = uVar4 + 1 & 0xff;
    local_dc[uVar4] = (char)uVar5;
    uVar4 = uVar4 + 1 & 0xff;
    local_dc[uVar4] = (char)((uint)local_2c >> 8);
    uVar4 = uVar4 + 1 & 0xff;
    local_dc[uVar4] = (char)local_2c;
    uVar4 = uVar4 + 1 & 0xff;
    local_dc[uVar4] = (char)((ushort)uVar6 >> 8);
    uVar4 = uVar4 + 1 & 0xff;
    local_dc[uVar4] = (char)uVar6;
    uVar4 = uVar4 + 1 & 0xff;
    local_dc[uVar4] = (char)(local_30 >> 8);
    uVar4 = uVar4 + 1 & 0xff;
    local_dc[uVar4] = (char)local_30;
    uVar3 = local_1c & 0xff;
    uVar4 = uVar4 + 1 & 0xff;
  } while (uVar3 < local_24);
  fw_0800c7c4(local_18,uVar4,1,local_dc,0xaa);
  return;
}

