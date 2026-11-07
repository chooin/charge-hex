// rea decompile_all
// name: fw_08002ae8
// address: 0x8002ae8
// body: available
// range: 0x8002ae8-0x8002c49 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


int fw_08002ae8(uint *param_1)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  char *pcVar6;
  int iVar7;
  uint uVar8;
  undefined1 local_50 [4];
  uint local_4c;
  char local_48 [16];
  uint local_38 [3];
  int local_2c;
  uint local_24;
  uint local_1c;
  uint *local_18;
  
  bVar2 = false;
  uVar8 = 0;
  iVar7 = 0;
  local_2c = 0;
  local_4c = 0;
  local_18 = param_1;
LAB_08002c3c:
  if (bVar2 || iVar7 != 0) {
    return iVar7;
  }
  bVar1 = false;
  local_24 = 0;
LAB_08002c34:
  do {
    if (bVar1 || iVar7 != 0) goto LAB_08002c3c;
    iVar3 = fw_08002250(0x20000448,local_38,5000);
    if (iVar3 != 0) {
      if (iVar3 == 2) {
        fw_08002448(0x18);
        uVar4 = 0x18;
LAB_08002b44:
        fw_08002448(uVar4);
        iVar7 = 2;
      }
      else {
        if (local_2c != 0) {
          uVar8 = uVar8 + 1;
        }
        if (uVar8 < 3) {
          uVar4 = 0x43;
        }
        else {
          fw_08002448(0x18);
          uVar4 = 0x18;
        }
LAB_08002c30:
        fw_08002448(uVar4);
      }
      goto LAB_08002c34;
    }
    uVar8 = 0;
    if (local_38[0] != 0) {
      if (local_38[0] == 2) {
        uVar4 = 6;
        goto LAB_08002b44;
      }
      if (DAT_2000044a != local_24) {
        uVar4 = 0x15;
        goto LAB_08002c30;
      }
      if (local_24 == 0) {
        if (DAT_2000044c == '\0') {
          fw_08002448(6);
          bVar1 = true;
          bVar2 = true;
          goto LAB_08002c34;
        }
        pcVar6 = &DAT_2000044c;
        for (uVar5 = 0; (*pcVar6 != '\0' && (uVar5 < 0x20)); uVar5 = uVar5 + 1) {
          *(char *)(uVar5 + 0x20000428) = *pcVar6;
          pcVar6 = pcVar6 + 1;
        }
        *(undefined1 *)(uVar5 + 0x20000428) = 0;
        uVar5 = 0;
        while( true ) {
          pcVar6 = pcVar6 + 1;
          if ((*pcVar6 == ' ') || (0xf < uVar5)) break;
          local_48[uVar5] = *pcVar6;
          uVar5 = uVar5 + 1;
        }
        local_48[uVar5] = '\0';
        fw_0800245c(local_48,&local_1c);
        *local_18 = local_1c;
        if (0xb801 < local_1c) {
          local_50[0] = 0x18;
          fw_08001cb8(&DAT_20000ba0,local_50,1,0x100000);
          fw_08001cb8(&DAT_20000ba0,local_50,1,0x100000);
          iVar7 = 5;
        }
        fw_08002448(6);
        uVar4 = 0x43;
LAB_08002c1e:
        fw_08002448(uVar4);
      }
      else {
        iVar3 = fw_08001df0(local_4c & 0xffff,&DAT_2000044c,local_38[0] & 0xffff);
        if (iVar3 == 0) {
          local_4c = local_4c + local_38[0];
          uVar4 = 6;
          goto LAB_08002c1e;
        }
        fw_08002448(0x18);
        fw_08002448(0x18);
        iVar7 = 4;
      }
      local_24 = local_24 + 1 & 0xff;
      local_2c = 1;
      goto LAB_08002c34;
    }
    fw_08002448(6);
    bVar1 = true;
  } while( true );
}

