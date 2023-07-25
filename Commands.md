# Commands

## 1\. Generate Key

|     |     |
| --- | --- |
| Description | Generate a public/private key pair and store the key pair at given zone. |
| Command Length | 3 bytes |
| Response Length | 33 bytes |

### Command:

|     |     |     |
| --- | --- | --- |
| Byte 0 | Byte 1 | Byte 2 |
| 0x4E | 0x4B | zone |

### Response:

|     |     |
| --- | --- |
| no abnormality | Return 33 bytes of the generated public key. |
| generation failed | Return 33 bytes of 0. |
| "zone" > 127 | There are only 128 zones available, from 0 to 127. <br>Return 33 bytes of 0, indicating fail of generation. |
| a public/private key pair already stored at given zone | No new key pair will be generated.<br>Return 33 bytes of the stored public key. |

* * *

## 2\. Read Public Key

|     |     |
| --- | --- |
| Description | Return the public key stored at specified zone. |
| Command Length | 3 bytes |
| Response Length | 33 bytes |

### Command:

|     |     |     |
| --- | --- | --- |
| Byte 0 | Byte 1 | Byte 2 |
| 0x52 | 0x50 | zone |

### Response:

|     |     |
| --- | --- |
| no abnormality | Return 33 bytes of the public key stored at specified zone. |
| "zone" > 127 | There are only 128 zones available, from 0 to 127. <br>Return 33 bytes of 0. |
| there is no key stored at given zone | Return 33 bytes of 0. |

* * *

## 3\. Sign

|     |     |
| --- | --- |
| Description | Generate signature on a 32 bytes string using given key. |
| Command Length | 35 bytes |
| Response Length | 64 bytes |

### Command:

|     |     |     |     |
| --- | --- | --- | --- |
| Byte 0 | Byte 1 | Byte 2 | Byte 3 .. Byte 34 |
| 0x53 | 0x48 | zone | 32 bytes of string to be signed |

### Response:

|     |     |
| --- | --- |
| no abnormality | Return 64 bytes of signature. |
| "zone" > 127 | There are only 128 zones available, from 0 to 127. <br>Return 64 bytes of 0. |
| there is no key stored at given zone | Return 64 bytes of 0. |

* * *

## 4\. Verify Signature

|     |     |
| --- | --- |
| Description | Verify signature for given public key, signature and 32 bytes string. |
| Command Length | 131 bytes |
| Response Length | 1 byte |

### Command:

|     |     |     |     |     |
| --- | --- | --- | --- | --- |
| Byte 0 | Byte 1 | Byte 2 .. Byte 34 | Byte 35.. Byte 98 | Byte 99.. Byte 130 |
| 0x56 | 0x53 | public key | signature | 32 bytes of string be signed |

### Response:

|     |     |
| --- | --- |
| pass | 0x01 |
| fail | 0x00 |

* * *

## 5\. Delete Key

|     |     |
| --- | --- |
| Description | Delete key pair stored at given zone, make it free to store a new generated key pair. |
| Command Length | 3 bytes |
| Response Length | 1 byte |

### Command:

|     |     |     |
| --- | --- | --- |
| Byte 0 | Byte 1 | Byte 3 |
| 0x44 | 0x4B | zone |

### Response:

|     |     |
| --- | --- |
| success | Return number of the given zone |
| fail | 0xFF(zone > 127) |