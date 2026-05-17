gcc main.c platform/platform-raylib.c -Wall -Wextra -o bin/mts26-0.1.0 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
if [ $? -ne 0 ]; then
    echo "Build failed"
    exit 1
fi
echo "Build succeeded"
exec bin/mts26-0.1.0