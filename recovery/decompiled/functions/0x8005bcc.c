// rea decompile_all
// name: fw_08005bcc
// address: 0x8005bcc
// body: available
// range: 0x8005bcc-0x8005d23 inclusive
// non_contiguous: false
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_08005bcc(uint *param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  for (uVar2 = 0; *param_2 >> (uVar2 & 0xff) != 0; uVar2 = uVar2 + 1) {
    uVar5 = 1 << (uVar2 & 0xff);
    uVar1 = *param_2 & uVar5;
    if (uVar1 != 0) {
      uVar3 = param_2[1];
      if ((((uVar3 == 1) || (uVar3 == 2)) || (uVar3 == 0x11)) || (uVar3 == 0x12)) {
        param_1[2] = param_2[3] << (uVar2 << 1 & 0xff) | param_1[2] & ~(3 << (uVar2 << 1 & 0xff));
        param_1[1] = (((byte)param_2[1] & 0x1f) >> 4) << (uVar2 & 0xff) | param_1[1] & ~uVar5;
      }
      uVar3 = uVar2 << 1;
      uVar5 = 3 << (uVar3 & 0xff);
      param_1[3] = param_2[2] << (uVar3 & 0xff) | param_1[3] & ~uVar5;
      if ((param_2[1] == 2) || (param_2[1] == 0x12)) {
        iVar4 = (uVar2 & 7) << 2;
        param_1[(uVar2 >> 3) + 8] =
             param_1[(uVar2 >> 3) + 8] & ~(0xf << iVar4) | param_2[4] << iVar4;
      }
      *param_1 = ((byte)param_2[1] & 3) << (uVar3 & 0xff) | *param_1 & ~uVar5;
      if ((int)(param_2[1] << 3) < 0) {
        _DAT_40021018 = _DAT_40021018 | 1;
        iVar4 = (uVar2 & 3) << 2;
        if (param_1 == (uint *)0x48000000) {
          iVar6 = 0;
        }
        else if (param_1 == (uint *)0x48000400) {
          iVar6 = 1;
        }
        else if (param_1 == (uint *)0x48000800) {
          iVar6 = 2;
        }
        else if (param_1 == (uint *)0x48000c00) {
          iVar6 = 3;
        }
        else {
          iVar6 = 5;
        }
        *(uint *)((uVar2 & 0xfffffffc) + 0x40010008) =
             iVar6 << iVar4 | *(uint *)((uVar2 & 0xfffffffc) + 0x40010008) & ~(0xf << iVar4);
        _DAT_40010400 = _DAT_40010400 & ~uVar1;
        if ((int)(param_2[1] << 0xf) < 0) {
          _DAT_40010400 = _DAT_40010400 | uVar1;
        }
        _DAT_40010404 = _DAT_40010404 & ~uVar1;
        if ((int)(param_2[1] << 0xe) < 0) {
          _DAT_40010404 = _DAT_40010404 | uVar1;
        }
        _DAT_40010408 = _DAT_40010408 & ~uVar1;
        if ((int)(param_2[1] << 0xb) < 0) {
          _DAT_40010408 = _DAT_40010408 | uVar1;
        }
        _DAT_4001040c = _DAT_4001040c & ~uVar1;
        if ((int)(param_2[1] << 10) < 0) {
          _DAT_4001040c = _DAT_4001040c | uVar1;
        }
      }
    }
  }
  return;
}

