# cf_client_pop_packet | [net](https://github.com/RandyGaul/cute_framework/blob/master/docs/net/README.md) | [cute_networking.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_networking.h)

Returns a packet from the server, if available.

```cpp
bool cf_client_pop_packet(CF_Client* client, void** packet, int* size, bool* was_sent_reliably);
```

Parameters | Description
--- | ---
client | The client.
packet | A pointer to the packet will be written here.
size | The size of `packet` will be written here, in bytes.
was_sent_reliably | `true` if the packet was a reliable packet.

## Return Value

Returns `true` if a packet was popped.

## Remarks

You must free this packet when you're done by calling [cf_client_free_packet](https://github.com/RandyGaul/cute_framework/blob/master/docs/net/cf_client_free_packet.md).

## Related Pages

[CF_Client](https://github.com/RandyGaul/cute_framework/blob/master/docs/net/cf_client.md)  
[cf_client_send](https://github.com/RandyGaul/cute_framework/blob/master/docs/net/cf_client_send.md)  
[cf_client_free_packet](https://github.com/RandyGaul/cute_framework/blob/master/docs/net/cf_client_free_packet.md)  
