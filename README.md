# Vigenère Cipher Application

## Overview
This project implements the Vigenère cipher, a method of encrypting alphabetic text through a simple form of polyalphabetic substitution. The implementation is done in C for performance and efficiency, integrated into a Node.js environment for ease of use and cross-platform scalability. This setup is ideal for developers looking for a cryptography solution with minimal DevOps configuration.

## Features
- **High Performance**: Implemented in C to leverage speed and efficiency.
- **Cross-Platform**: Integrated with Node.js, making it runnable on any platform that supports Node.js (Windows, macOS, Linux).
- **Minimal Setup**: Easy setup process, thanks to Node.js and a small amount of required DevOps configuration.
- **Scalable**: Designed to be easily scalable across multiple environments and machines.

## Prerequisites
Before you begin, ensure you have the following installed:
- [Node.js](https://nodejs.org/en/download/) (version 12.x or later)
- [npm](https://npmjs.com/) (usually included with Node.js)
- A C compiler like gcc (for compiling the C module)

## Installation
Follow these steps to get the application running on your local machine:

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/vigenere-cipher.git
   cd vigenere-cipher

2. **Install dependencies and make build:**
    ```npm install```

## Usage
To use the application, you need to provide a key and specify whether you want to encrypt or decrypt text. The application reads from a file named env.json for encryption and outputs to env.enc.json, and vice versa for decryption.

**Use this script to start**
```./scripts/start.sh```

## Configuring
The application requires minimal configuration, handled through environment variables. Make sure to set these in your .env file or directly in your environment:

KEY: The encryption/decryption key used by the cipher.

## Acknowledgments
- (Wiki)[https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher#:~:text=The%20Vigen%C3%A8re%20cipher%20(French%20pronunciation,of%20another%20text%2C%20the%20key.]
- (node-addon-api)[https://github.com/nodejs/node-addon-api]
