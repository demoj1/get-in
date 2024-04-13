Work with json in scripts without 228GB node_modules dependency

```bash
:: C/get_in » echo '{"a": [1, {"b": 2}]}' | get-in a
[1, {
        "b":    2
}]
```

```bash
:: C/get_in » echo '{"a": [1, {"b": 2}]}' | get-in a.0
1
```

```bash
:: C/get_in » echo '{"a": [1, {"b": 2}]}' | get-in a.1
{
        "b":    2
}
```

```bash
:: C/get_in » echo '{"a": [1, {"b": 2}]}' | get-in a.1.b
2
```

```bash
:: C/get_in » echo '{"a": [1, {"b": 2}]}' | get-in a.1.b.c
[ERROR] Could not extract sub path from plain type
```

```bash
:: C/get_in » echo '{"a": [1, {"b": 2}]}' | get-in c
(null)
```