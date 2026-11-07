// rea decompile_all
// name: fw_0800bb7c
// address: 0x800bb7c
// body: available
// range: 0x800bb7c-0x800bc25 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_0800bb7c(int param_1,int param_2,undefined1 param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_1c;
  
  uVar2 = 0;
  if (_DAT_200000d4 != param_5) {
    iVar3 = param_1 * 0x34;
    if ((param_2 == 0) ||
       ((local_1c = param_3, param_4 == 0 && (*(char *)(iVar3 + 0x200005df) == '\0')))) {
      local_1c = 0;
    }
    if (*(short *)(&DAT_200005da + iVar3) == 0) {
      DAT_200008c1 = 0xff;
    }
    else {
      DAT_200008c1 = 1;
    }
    _DAT_200000d4 = param_5;
    DAT_200009fa = (undefined1)param_1;
    DAT_200009fb = (undefined1)((uint)param_2 >> 8);
    DAT_200009fc = (undefined1)param_2;
    DAT_200009fd = (undefined1)((uint)param_4 >> 8);
    DAT_200009fe = (undefined1)param_4;
    uVar1 = *(undefined4 *)(iVar3 + 0x200005d0);
    uVar2 = 0x12;
    DAT_200009ff = (undefined1)((uint)uVar1 >> 0x18);
    DAT_20000a00 = (undefined1)((uint)uVar1 >> 0x10);
    DAT_20000a01 = (undefined1)((uint)uVar1 >> 8);
    DAT_20000a02 = (undefined1)uVar1;
    DAT_20000a03 = (undefined1)((ushort)*(undefined2 *)(iVar3 + 0x200005be) >> 8);
    DAT_20000a04 = (undefined1)*(undefined2 *)(iVar3 + 0x200005be);
    DAT_20000a06 = (undefined1)*(short *)(&DAT_200005da + iVar3);
    DAT_20000a07 = local_1c;
    DAT_20000a08 = (undefined1)((uint)param_5 >> 0x18);
    DAT_20000a09 = (undefined1)((uint)param_5 >> 0x10);
    DAT_20000a0a = (undefined1)((uint)param_5 >> 8);
    DAT_20000a0b = (undefined1)param_5;
    DAT_20000a05 = DAT_200008c1;
  }
  fw_0800c7c4(0x2c,uVar2,1,&DAT_200009fa,0xaa);
  return;
}

