#include <stdio.h>
#include <stdlib.h>

// Patches falloutwHR.exe to fix a null pointer bug

int main(void) {
  printf("[+] Opening falloutwHR.exe to be patched\n");
  FILE* gameFile = fopen("falloutwHR.exe", "r+");

  unsigned int caveOffset = 0xAABE;
  char patchFunction[]  = //
    "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
    "\x90\x90\x90\x90\x90\x90\x90\x8B\x5E\x04\x8B\x16"
    "\x83\xF8\x00\x74\x05\xE8\x20\xDA\x00\x00\xE9\x6F"
    "\xDB\x00\x00\x90\x90\x90\x90\x90\x90\x90\x90\x90"
    "\x90";
  fseek(gameFile, caveOffset, SEEK_SET);
  fwrite(&patchFunction, sizeof(patchFunction)-1, 1, gameFile);

  int hookOffset = 0x1864F;
  char hookFunction[] = //
    "\xE9\x7D\x24\xFF\xFF\x90\x90\x90\x90\x90";
  fseek(gameFile, hookOffset, SEEK_SET);
  fwrite(&hookFunction, sizeof(hookFunction)-1, 1, gameFile);

  printf("[+] Game patched\n");
  fclose(gameFile);

  return 0;
}

