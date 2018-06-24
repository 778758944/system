#!/usr/bin
clang -o websocket main.c websocket.c ./deps/b64/encode.c ./deps/b64/decode.c -L /usr/local/opt/openssl/lib -l crypto
