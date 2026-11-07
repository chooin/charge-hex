// rea decompile_all
// name: fw_0800bab4
// address: 0x800bab4
// body: available
// range: 0x800bab4-0x800bb35 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_0800bab4(undefined1 param_1,undefined4 param_2,undefined4 param_3,undefined1 param_4,
                undefined4 param_5,int param_6)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (_DAT_200000d0 != param_6) {
    if (DAT_200008c0 == '\0') {
      DAT_200008c1 = 0xff;
    }
    else {
      DAT_200008c1 = 0;
    }
    _DAT_200000d0 = param_6;
    uVar1 = 0x13;
    DAT_200009dd = (undefined1)((uint)param_2 >> 8);
    DAT_200009de = (undefined1)param_2;
    DAT_200009df = (undefined1)((uint)param_3 >> 8);
    DAT_200009e0 = (undefined1)param_3;
    DAT_200009e2 = (undefined1)_DAT_20000882;
    DAT_200009e3 = (undefined1)((uint)_DAT_2000089c >> 0x18);
    DAT_200009e4 = (undefined1)((uint)_DAT_2000089c >> 0x10);
    DAT_200009e5 = (undefined1)((uint)_DAT_2000089c >> 8);
    DAT_200009e6 = (undefined1)_DAT_2000089c;
    DAT_200009e7 = (undefined1)((ushort)_DAT_20000886 >> 8);
    DAT_200009e8 = (undefined1)_DAT_20000886;
    DAT_200009ea = DAT_200008c0;
    DAT_200009eb = (undefined1)((uint)param_6 >> 0x18);
    DAT_200009ec = (undefined1)((uint)param_6 >> 0x10);
    DAT_200009ed = (undefined1)((uint)param_6 >> 8);
    DAT_200009ee = (undefined1)param_6;
    DAT_200009dc = param_1;
    DAT_200009e1 = param_4;
    DAT_200009e9 = DAT_200008c1;
  }
  fw_0800c7c4(0x2d,uVar1,1,&DAT_200009dc,0xaa);
  return;
}

