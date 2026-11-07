// rea decompile_all
// name: fw_0800c85c
// address: 0x800c85c
// body: available
// range: 0x800c85c-0x800c879 inclusive
// range: 0x800c88a-0x800ca2b inclusive
// non_contiguous: true
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; Ghidra Listing reports a terminal call at 0x800c876 to 0x800c91e (callee identity unknown), 0x800c93e (callee identity unknown), 0x800c8fa (callee identity unknown), 0x800c8d6 (callee identity unknown), 0x80095d2 __ARM_common_switch8 (external=false, thunk=false, hasNoReturn=false), 0x800c8b2 (callee identity unknown), 0x800c8b0 (callee identity unknown), 0x800c88a (callee identity unknown), 0x800c9e8 (callee identity unknown), 0x800ca08 (callee identity unknown), 0x800c9a4 (callee identity unknown), 0x800c9c4 (callee identity unknown), 0x800c962 (callee identity unknown), 0x800c982 (callee identity unknown); fallthrough is excluded by Ghidra's flow model. The reason for the terminal flow is not established by this observation.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Function: __ARM_common_switch8 replaced with injection: switch8_r3 */
/* WARNING (jumptable): Removing unreachable block (ram,0x0800c876) */
/* WARNING: Removing unreachable block (ram,0x0800c876) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void fw_0800c85c(char param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  
  if (0xc < (byte)(param_1 + 1U)) {
    return;
  }
  switch(param_1) {
  case '\0':
    if (param_2 == 0) {
      _DAT_200000b8 = _DAT_200000b8 & 0xfffffffe;
      bVar1 = DAT_200000dd & 0xfd;
      bVar2 = 1;
    }
    else {
      _DAT_200000b8 = _DAT_200000b8 | 1;
      bVar1 = DAT_200000dd & 0xfe;
      bVar2 = 2;
    }
    break;
  case '\x01':
    if (param_2 == 0) {
      _DAT_200000b8 = _DAT_200000b8 & 0xfffffffd;
      bVar1 = DAT_200000dd & 0xf7;
      bVar2 = 4;
    }
    else {
      _DAT_200000b8 = _DAT_200000b8 | 2;
      bVar1 = DAT_200000dd & 0xfb;
      bVar2 = 8;
    }
    break;
  case '\x02':
    if (param_2 == 0) {
      _DAT_200000b8 = _DAT_200000b8 & 0xfffffffb;
      bVar1 = DAT_200000dd & 0xdf;
      bVar2 = 0x10;
    }
    else {
      _DAT_200000b8 = _DAT_200000b8 | 4;
      bVar1 = DAT_200000dd & 0xef;
      bVar2 = 0x20;
    }
    break;
  case '\x03':
    if (param_2 == 0) {
      _DAT_200000b8 = _DAT_200000b8 & 0xfffffff7;
      bVar1 = DAT_200000dd & 0x7f;
      bVar2 = 0x40;
    }
    else {
      _DAT_200000b8 = _DAT_200000b8 | 8;
      bVar1 = DAT_200000dd & 0xbf;
      bVar2 = 0x80;
    }
    break;
  case '\x04':
    if (param_2 != 0) {
      _DAT_200000b8 = _DAT_200000b8 | 0x10;
      bVar1 = DAT_200000de & 0xfe;
      bVar2 = 2;
LAB_0800c99e:
      DAT_200000de = bVar1 | bVar2;
      return;
    }
    _DAT_200000b8 = _DAT_200000b8 & 0xffffffef;
    bVar2 = DAT_200000de & 0xfd;
    bVar1 = 1;
    goto LAB_0800c95c;
  case '\x05':
    if (param_2 == 0) {
      _DAT_200000b8 = _DAT_200000b8 & 0xffffffdf;
      bVar2 = DAT_200000de & 0xf7;
      bVar1 = 4;
    }
    else {
      _DAT_200000b8 = _DAT_200000b8 | 0x20;
      bVar2 = DAT_200000de & 0xfb;
      bVar1 = 8;
    }
    goto LAB_0800c95c;
  case '\x06':
    if (param_2 == 0) {
      _DAT_200000b8 = _DAT_200000b8 & 0xffffffbf;
      bVar2 = DAT_200000de & 0xdf;
      bVar1 = 0x10;
    }
    else {
      _DAT_200000b8 = _DAT_200000b8 | 0x40;
      bVar2 = DAT_200000de & 0xef;
      bVar1 = 0x20;
    }
    goto LAB_0800c95c;
  case '\a':
    if (param_2 == 0) {
      _DAT_200000b8 = _DAT_200000b8 & 0xffffff7f;
      bVar1 = DAT_200000de & 0x7f;
      bVar2 = 0x40;
      goto LAB_0800c99e;
    }
    bVar1 = 0x80;
    _DAT_200000b8 = _DAT_200000b8 | 0x80;
    bVar2 = DAT_200000de & 0xbf;
LAB_0800c95c:
    DAT_200000de = bVar2 | bVar1;
    return;
  case '\b':
    if (param_2 != 0) {
      _DAT_200000b8 = _DAT_200000b8 | 0x100;
      bVar1 = DAT_200000df & 0xfe;
      bVar2 = 2;
LAB_0800ca26:
      DAT_200000df = bVar1 | bVar2;
      return;
    }
    _DAT_200000b8 = _DAT_200000b8 & 0xfffffeff;
    bVar2 = DAT_200000df & 0xfd;
    bVar1 = 1;
    goto LAB_0800c9e2;
  case '\t':
    if (param_2 == 0) {
      _DAT_200000b8 = _DAT_200000b8 & 0xfffffdff;
      bVar2 = DAT_200000df & 0xf7;
      bVar1 = 4;
    }
    else {
      _DAT_200000b8 = _DAT_200000b8 | 0x200;
      bVar2 = DAT_200000df & 0xfb;
      bVar1 = 8;
    }
    goto LAB_0800c9e2;
  case '\n':
    if (param_2 == 0) {
      _DAT_200000b8 = _DAT_200000b8 & 0xfffffbff;
      bVar2 = DAT_200000df & 0xdf;
      bVar1 = 0x10;
    }
    else {
      _DAT_200000b8 = _DAT_200000b8 | 0x400;
      bVar2 = DAT_200000df & 0xef;
      bVar1 = 0x20;
    }
    goto LAB_0800c9e2;
  case '\v':
    if (param_2 == 0) {
      _DAT_200000b8 = _DAT_200000b8 & 0xfffff7ff;
      bVar1 = DAT_200000df & 0x7f;
      bVar2 = 0x40;
      goto LAB_0800ca26;
    }
    _DAT_200000b8 = _DAT_200000b8 | 0x800;
    bVar2 = DAT_200000df & 0xbf;
    bVar1 = 0x80;
LAB_0800c9e2:
    DAT_200000df = bVar2 | bVar1;
    return;
  default:
    goto switchD_0800c876_caseD_ff;
  }
  DAT_200000dd = bVar1 | bVar2;
switchD_0800c876_caseD_ff:
  return;
}

