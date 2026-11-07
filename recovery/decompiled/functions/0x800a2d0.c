// rea decompile_all
// name: fw_0800a2d0
// address: 0x800a2d0
// body: available
// range: 0x800a2d0-0x800a2e5 inclusive
// range: 0x800a2f8-0x800a379 inclusive
// non_contiguous: true
// provider: Ghidra 12.1.4 (ghidra)
// analysis_profile: 5521f6a294496a59a8f6086766d9ccc38e7c27094d4d07eb6e3566c68cdf44c9
// limitations: The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results.; The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written.; Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again.; Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>.; Ghidra Listing reports a terminal call at 0x800a2e2 to 0x800a2f8 (callee identity unknown), 0x800a318 (callee identity unknown), 0x800a338 (callee identity unknown), 0x800a358 (callee identity unknown), 0x80095d2 __ARM_common_switch8 (external=false, thunk=false, hasNoReturn=false), 0x800a330 (callee identity unknown), 0x800a350 (callee identity unknown), 0x800a370 (callee identity unknown), 0x800a30a (callee identity unknown), 0x800a328 (callee identity unknown), 0x800a348 (callee identity unknown), 0x800a368 (callee identity unknown), 0x800a306 (callee identity unknown), 0x800a320 (callee identity unknown), 0x800a340 (callee identity unknown), 0x800a360 (callee identity unknown); fallthrough is excluded by Ghidra's flow model. The reason for the terminal flow is not established by this observation.; macOS sessions require a matching executable Ghidra native decompiler; REA checks for it but does not build native components or change Gatekeeper quarantine state.; Ghidra analysis was seeded before auto-analysis from /Users/zhuning/Projects/charge/charge-hex/recovery/ghidra/seeds.tsv (sha256 656a3db3efd5d2a5a6d10d504ea142b7caf9e5db0c73c5588d646252a056e5df: 5 function, 0 code, 0 label entries). Seeded functions, code and names are caller assertions, not Ghidra discoveries.; Seed outcome: 5 functions created, 0 already present, 0 failed; 0 code seeds decoded, 0 failed; 0 labels applied, 0 failed; 0 seeds outside initialized memory.; Pseudocode is Ghidra decompiler output, not original source and not text-equivalent to Hopper output.; External functions and functions without an analyzable body return null; other decompiler failures remain explicit.
// pseudocode: provider-specific; not original source


/* WARNING: Function: __ARM_common_switch8 replaced with injection: switch8_r3 */
/* WARNING (jumptable): Removing unreachable block (ram,0x0800a2e2) */
/* WARNING: Removing unreachable block (ram,0x0800a2e2) */

uint fw_0800a2d0(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (0xe < param_1 - 1U) {
    return 0;
  }
  uVar4 = 0x48000000;
  uVar1 = 0;
  switch(param_1) {
  case 1:
    uVar3 = 1;
    uVar4 = 0x48000400;
    goto LAB_0800a30e;
  case 2:
    uVar3 = 0x80;
    goto LAB_0800a30e;
  case 3:
    uVar3 = 0x40;
LAB_0800a30e:
    iVar2 = fw_08005d3c(uVar4,uVar3);
    if (iVar2 != 0) {
      return 0;
    }
    uVar1 = 1;
switchD_0800a2e2_default:
    return uVar1;
  case 4:
    iVar2 = fw_080082e8(0);
    uVar1 = iVar2 << 0x13;
    break;
  case 5:
    iVar2 = fw_080082e8(0);
    uVar1 = iVar2 << 0x12;
    break;
  case 6:
    iVar2 = fw_080082e8(0);
    uVar1 = iVar2 << 0x11;
    break;
  case 7:
    uVar1 = fw_080082e8(0);
    return uVar1 >> 0xf;
  case 8:
    iVar2 = fw_080082e8(0);
    uVar1 = iVar2 << 0x17;
    break;
  case 9:
    iVar2 = fw_080082e8(0);
    uVar1 = iVar2 << 0x16;
    break;
  case 10:
    iVar2 = fw_080082e8(0);
    uVar1 = iVar2 << 0x15;
    break;
  case 0xb:
    iVar2 = fw_080082e8(0);
    uVar1 = iVar2 << 0x14;
    break;
  case 0xc:
    iVar2 = fw_080082e8(0);
    uVar1 = iVar2 << 0x1b;
    break;
  case 0xd:
    iVar2 = fw_080082e8(0);
    uVar1 = iVar2 << 0x1a;
    break;
  case 0xe:
    iVar2 = fw_080082e8(0);
    uVar1 = iVar2 << 0x19;
    break;
  case 0xf:
    iVar2 = fw_080082e8(0);
    uVar1 = iVar2 << 0x18;
    break;
  default:
    goto switchD_0800a2e2_default;
  }
  return uVar1 >> 0x1f;
}

