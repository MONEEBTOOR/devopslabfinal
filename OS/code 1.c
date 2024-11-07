#!/bin/bash

# Hashed correct password (for "warning") using SHA-256
# Note: This is a hash for the demonstration; in a real environment, securely store and retrieve this hash.
correct_hash="a2f70e01bb4e1dbdd95d4dfad6b6a6c47f1083b06af14df6dc27a5015ddf2fc6"

# Function to hash input password for comparison
hash_password() {
    echo -n "$1" | sha256sum | awk '{print $1}'
}

# Authentication prompt
while true; do
    # Prompt the user for the password
    read -s -p "Enter password: " input_password
    echo

    # Hash the user input and compare it to the correct hash
    if [ "$(hash_password "$input_password")" == "$correct_hash" ]; then
        echo "Access granted."
        break
    else
        echo "Sorry, try again."
    fi
done
#!/bin/bash

# Hashed correct password (for "warning") using SHA-256
# Note: This is a hash for the demonstration; in a real environment, securely store and retrieve this hash.
correct_hash="a2f70e01bb4e1dbdd95d4dfad6b6a6c47f1083b06af14df6dc27a5015ddf2fc6"

# Function to hash input password for comparison
hash_password() {
    echo -n "$1" | sha256sum | awk '{print $1}'
}

# Authentication prompt
while true; do
    # Prompt the user for the password
    read -s -p "Enter password: " input_password
    echo

    # Hash the user input and compare it to the correct hash
    if [ "$(hash_password "$input_password")" == "$correct_hash" ]; then
        echo "Access granted."
        break
    else
        echo "Sorry, try again."
    fi
done