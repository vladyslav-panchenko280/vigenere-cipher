#!/bin/bash

start() {
    if [ ! -d "dist" ]; then
        echo "Directory 'dist' does not exist. Running 'npm run pretest'..."
        npm run pretest
        echo "Pretest complete."
    else
        echo "Directory 'dist' exists."
    fi

    read -p "Enter the encryption key: " key
    while [[ -z "$key" ]]; do
        echo "Key cannot be empty. Please enter a valid key."
        read -p "Enter the encryption key: " key
    done

    read -p "Enter the modificator (--encrypt/--decrypt): " mod
    while [[ "$mod" != "--encrypt" && "$mod" != "--decrypt" ]]; do
        echo "Invalid modificator. Use '--encrypt' or '--decrypt'."
        read -p "Enter the modificator (--encrypt/--decrypt): " mod
    done

    node ./dist/binding.js "$key" "$mod"
}

start
