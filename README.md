# arcfour - Lightweight RC4 Encryption Library

**arcfour** is a small, easy-to-use, and production-ready RC4 (Arcfour) encryption library written in C. It provides a simple interface for encrypting and decrypting data with any key, suitable for embedding in any C project.  

This library also includes an important security improvement: the first 256 bytes of the key stream are discarded to reduce known vulnerabilities in the classic RC4 algorithm.  

---

## Features

- Fully implemented RC4 (Arcfour) algorithm in C  
- Discards first 256 key stream bytes for better security  
- Easy-to-use API: `rc4init`, `rc4byte`, `rc4encrypt`  
- Cross-platform (Windows/Linux with GCC/MinGW)  
- Can be used as a static library (`libarcfour.a`)  
- No external dependencies  

---

## Installation (Windows)

1. Clone the repository:

```bash
git clone https://github.com/<your-username>/arcfour.git
cd arcfour
