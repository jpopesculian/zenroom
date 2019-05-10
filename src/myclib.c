#include <stdio.h>
#include <stdlib.h>
#include <sodium.h>
#include <string.h>

#ifdef __cplusplus
  #include "lua.hpp"
#else
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
#endif

#ifdef __cplusplus
extern "C"{
#endif

static int create_keypair(lua_State *L) {
    unsigned char pk[crypto_sign_PUBLICKEYBYTES];
    unsigned char sk[crypto_sign_SECRETKEYBYTES];
    crypto_sign_keypair(pk, sk);

    lua_pushstring(L, pk);
    lua_pushstring(L, sk);

    return 2;
}

static int base64_encode(lua_State *L) {
    const int variant = sodium_base64_VARIANT_ORIGINAL;
    const unsigned char * const bin = luaL_checkstring(L, 1);
    const size_t bin_len = strlen(bin);
    const size_t b64_maxlen = sodium_base64_encoded_len(bin_len, variant);
    char b64[b64_maxlen];
    sodium_bin2base64(b64, b64_maxlen, bin, bin_len, variant);

    lua_pushstring(L, b64);
    return 1;
}

static const struct luaL_Reg myclib [] = {
    {"create_keypair", create_keypair},
    {"base64_encode", base64_encode},
    {NULL, NULL}
};

int luaopen_myclib (lua_State *L) {
    luaL_newlib(L, myclib);
    return 1;
}

#ifdef __cplusplus
}
#endif
