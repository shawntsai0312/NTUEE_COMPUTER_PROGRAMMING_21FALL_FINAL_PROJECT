# Computer Programming Final Project

##### author: B10901176 蔡弘祥

### Before Running

1. **download sfml**
    ```shell
    brew install sfml
    ```
2. **check the path of sfml is the same in makefile**
   
   - In my case, the path is `/opt/homebrew/sfml`

    ```makefile
    # Variables
    CC = g++
    CFLAGS = -Wall -O3 -I/opt/homebrew/opt/sfml/include
    LDFLAGS = -L/opt/homebrew/opt/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system
    ```

### How To Run

```shell
./run.sh
```

### How To Set VS code c++ include path configurations

- Add the path to "includePath"

```json
{
    "configurations": [
        {
            "name": "Mac",
            "includePath": [
                "${workspaceFolder}/**",
                "/opt/homebrew/opt/sfml/include",
            ],
            "defines": [],
            "macFrameworkPath": [
                "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks"
            ],
            "compilerPath": "/usr/bin/clang",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "macos-clang-arm64"
        }
    ],
    "version": 4
}
```