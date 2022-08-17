#!/usr/bin
clang -o websocket -I /opt/homebrew/opt/openssl/include main.c websocket.c ./deps/b64/encode.c ./deps/b64/decode.c -L /opt/homebrew/opt/openssl/lib -l crypto
