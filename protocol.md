#### LOGIN
```cpp
    Json json{
        {"type", LOGIN},
        {"id", id},
        {"password", password},
        {"fd", sourcefd}   // server-addin
    };
```
#### LOGINRET
```cpp
    Json ret{
        {"type", LOGINRET},
        {"result", "ERROR"}
    };
```
#### REG
```cpp
    Json json{
            {"type", REG},
            {"name", name},
            {"password", password}
            {"fd", sourcefd}   // server-addin
    };
```
#### REGRET
```cpp
    Json ret{
            {"type", REGRET},
            {"result", "ERROR"},
            {"id", -1}
    };
```
#### CHAT
```cpp
    Json json{
        {"type", CHAT},
        {"sender", chatid},
        {"content", str}
        {"fd", sourcefd}   // server-addin
    };
```
#### CHATRET
```cpp
    Json msgret{
            {"type", CHATRET},
            {"result", "OK"}
    };
```
#### CHATMSG
区分CHAT，CHATMSG为客户端接收到的消息
```cpp
    Json msgall{
        {"type", CHATMSG},
        {"sender", sender_name},
        {"content", msg["content"]}
    };
```