# Cloudflare example

## Run (development)

```shell
npx wrangler dev index.js

```

To test, call the service with curl (or alike) with the supplied model.bin

```shell
curl --location 'http://127.0.0.1:8787/' --header 'Content-Type: application/octet-stream' --data '@model.bin'

```
