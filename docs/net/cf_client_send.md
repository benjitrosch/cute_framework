# cf_client_send | [net](https://github.com/RandyGaul/cute_framework/blob/master/docs/net/README.md) | [cute_networking.h](https://github.com/RandyGaul/cute_framework/blob/master/include/cute_networking.h)

Sends a packet to the server.

```cpp
CF_Result cf_client_send(CF_Client* client, const void* packet, int size, bool send_reliably);
```

Parameters | Description
--- | ---
client | The client.
packet | The packet.
size | The size of `packet` in bytes.
send_reliably | If `true` the packet will be sent reliably and in order. If false, the packet will be sent just once, and it
                   may arrive out of order, or not at all.

## Return Value

Returns any errors as a [CF_Result](https://github.com/RandyGaul/cute_framework/blob/master/docs/utility/cf_result.md).

## Remarks

If the packet size is too large (over 1k bytes) it will be split up and sent in smaller chunks.

`send_reliably` as true means the packet will be sent reliably an in-order relative to other
reliable packets. Under packet loss the packet will continually be sent until an acknowledgement
from the server is received. False means to send a typical UDP packet, with no special mechanisms
regarding packet loss.

Reliable packets are significantly more expensive than unreliable packets, so try to send any data
that can be lost due to packet loss as an unreliable packet. Of course, some packets are required
to be sent, and so reliable is appropriate. As an optimization some kinds of data, such as frequent
transform updates, can be sent unreliably.

## Related Pages

[CF_Client](https://github.com/RandyGaul/cute_framework/blob/master/docs/net/cf_client.md)  
[cf_client_pop_packet](https://github.com/RandyGaul/cute_framework/blob/master/docs/net/cf_client_pop_packet.md)  
[cf_client_free_packet](https://github.com/RandyGaul/cute_framework/blob/master/docs/net/cf_client_free_packet.md)  
