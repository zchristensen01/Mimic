# Stage 0: The Single Joint

PlatformIO project for the Arduino UNO. Thirteen sessions, S0 to S12, in
[the Stage 0 Workbook](../../docs/guides/Mimic_Stage0_Workbook.md), which holds the pin map, the
constants and the exit gate.

```bash
pio run   -e uno                  # compile
pio run   -e uno -t upload        # compile and flash
pio device monitor -b 250000      # serial monitor
pio test  -e native               # host-side unit tests, no board attached
```

CI runs `pio run -e uno` on every push. `pio test -e native` cannot pass until the classes have
implementations; it is enabled in CI at S12.

S12 rewrites this file.
