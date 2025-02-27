#### LOGIN
```cpp
    Json json{
        {"type", "login"},
        {"id", id},
        {"password", password},
        {"fd", sourcefd}   // server-addin
    };
```
#### LOGINRET
```cpp

```
#### REG
```cpp
    Json json{
            {"type", "reg"},
            {"name", name},
            {"password", password}
            {"fd", sourcefd}   // server-addin
    };
```
#### REGRET
```cpp

```
#### CHAT
```cpp
    Json json{
        {"type", "chat"},
        {"sender", chatid},
        {"content", str}
        {"fd", sourcefd}   // server-addin
    };
```
#### CHATRET
```cpp

```