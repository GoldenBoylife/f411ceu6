# STM32F411CEU6 Firmware

STM32F411CEU6 기반의 임베디드 펌웨어 프로젝트를 관리하는 저장소입니다.

현재 주요 프로젝트는 **PetBot Robotics**의 하위 제어 펌웨어입니다.  
Raspberry Pi가 AI, 음성 처리 및 상위 명령 생성을 담당하고, STM32F411CEU6은 UART로 전달받은 명령을 기반으로 서보모터, LED, 버튼 등 실시간 하드웨어를 제어하는 구조를 목표로 개발하고 있습니다.

> PetBot 전체 개발 과정과 작업 로그는 [GoldenBoy 개발 홈페이지](https://goldenboy.co.kr)의 **PetBot** 페이지에서 확인할 수 있습니다.

---

## Main Project

### `f411ceu6_petbot_servo`

PetBot Robotics의 STM32 기반 하위 제어기 펌웨어입니다.

현재 구현 내용은 다음과 같습니다.

- TIM PWM 기반 서보모터 2채널 제어
- GPIO 공통 드라이버 구성
- Active High / Active Low 장치의 논리 상태 통합
- LED 및 Button 모듈 분리
- UART DMA 기반 수신 버퍼
- 보드별 핀과 주변장치 정보를 분리하기 위한 BSP 구조
- Raspberry Pi 연동을 위한 텍스트 프로토콜 설계
- 두 서보모터의 목표 각도 및 속도 기반 동시 업데이트 구조 설계

향후 구현 예정 기능은 다음과 같습니다.

- `<POSE,90,45,30>` 형식의 UART 명령 처리
- 서보모터 비동기 이동 및 주기적 업데이트
- 두 서보모터의 동시 시작과 동기화 제어
- 끄덕임 및 고개 흔들기 모션
- LED 제어 명령
- Raspberry Pi Zero와 STM32 간 명령 및 상태 통신
- LCD 또는 OLED 기반 표정 출력 연동

---

## System Architecture

```text
Raspberry Pi
 ├─ LLM API
 ├─ STT / TTS
 ├─ 상위 명령 및 행동 결정
 └─ UART 명령 전송
          ↓
STM32F411CEU6
 ├─ Protocol
 ├─ Motion Control
 ├─ Servo Control
 ├─ LED / Button
 └─ 실시간 하드웨어 제어
```

펌웨어 내부 구조는 다음과 같이 분리하는 것을 목표로 합니다.

```text
Application
 ├─ Protocol
 └─ Control
      ↓
Device
      ↓
Driver
      ↓
BSP
      ↓
STM32 HAL
```

- **Application**  
  프로젝트 초기화, 메인 루프 및 각 모듈의 실행 흐름을 관리합니다.

- **Protocol**  
  UART에서 수신한 텍스트 데이터를 PetBot 명령으로 변환합니다.

- **Control**  
  끄덕임, 고개 흔들기 등 여러 장치를 조합한 로봇 동작을 관리합니다.

- **Device**  
  Servo, LED, Button, LCD, OLED, Ultrasonic Sensor 등 실제 장치 단위 기능을 담당합니다.

- **Driver**  
  GPIO, UART, SPI, I2C, Timer 등 MCU 주변장치의 공통 인터페이스를 담당합니다.

- **BSP**  
  프로젝트별 GPIO Port/Pin, UART Handle, Timer Channel 등 실제 하드웨어 매핑을 담당합니다.

---

## Repository Structure

```text
f411ceu6/
├─ f411ceu6_petbot_servo/
│  ├─ App/
│  │  ├─ ap.c
│  │  ├─ ap.h
│  │  ├─ def.h
│  │  ├─ bsp/
│  │  ├─ protocol/
│  │  └─ control/
│  │
│  ├─ Modules/
│  │  ├─ driver/
│  │  ├─ device/
│  │  └─ common/
│  │
│  ├─ Core/
│  ├─ Drivers/
│  └─ *.ioc
│
├─ legacy/
│  └─ 이전 STM32F411 테스트 및 펌웨어 프로젝트
│
├─ .gitignore
└─ README.md
```

현재 구조를 점진적으로 다음 기준에 맞춰 정리하고 있습니다.

```text
App/
→ PetBot 프로젝트에 종속되는 코드

Modules/
→ 여러 펌웨어 프로젝트에서 재사용할 수 있는 자체 모듈

Core/, Drivers/
→ STM32CubeMX 및 STM32 HAL 생성 코드

legacy/
→ 이전 실습, 테스트 및 구조 변경 전 프로젝트
```

---

## Module Classification

### Driver

MCU 주변장치를 공통 인터페이스로 감싸는 저수준 모듈입니다.

```text
gpio
uart
spi
i2c
timer
pwm
```

예시:

```c
gpioWrite(ch, true);
uartWrite(ch, data, length);
```

### Device

Driver를 이용하여 실제 장치의 기능을 제공하는 모듈입니다.

```text
led
button
servo
lcd
oled
ultrasonic
```

예시:

```c
ledOn(ch);
btnRead(ch);
servoSetTarget(ch, angle, speed);
```

### Common

특정 보드나 장치에 종속되지 않는 공통 코드입니다.

```text
ring_buffer
crc
text_frame
string utilities
```

### Protocol

Raspberry Pi와 STM32 사이의 명령 형식을 정의하고 파싱합니다.

초기 프로토콜은 디버깅이 쉬운 텍스트 형식을 사용합니다.

```text
<POSE,90,45,30>
<LED,0,1>
<MOTION,NOD,1,30>
```

### Control

여러 Device를 조합하여 로봇의 동작을 구현합니다.

```text
끄덕이기
고개 흔들기
중립 자세
표정과 모션 연동
```

---

## Hardware

- STM32F411CEU6 Black Pill
- SG90 / MG90S / ES90 계열 서보모터
- 외부 LED 및 User LED
- Push Button
- Raspberry Pi Zero 계열 보드
- UART 통신
- LCD 또는 OLED 디스플레이 예정

---

## Development Environment

- STM32CubeIDE
- STM32CubeMX
- C
- STM32 HAL
- Git
- Windows / MobaXterm

---

## Firmware Binary

`.bin`과 `.hex` 파일은 개발 PC에서 빌드한 펌웨어를 다른 PC 또는 노트북에서 바로 업로드할 수 있도록 저장소에 포함합니다.

빌드 중간 산출물 전체를 관리하기보다는, 최종 업로드에 필요한 펌웨어 파일을 별도로 관리하는 방향을 사용합니다.

예정 구조:

```text
Release/
├─ petbot_servo.bin
└─ petbot_servo.hex
```

---

## Development Direction

이 저장소는 단순한 GPIO 및 PWM 예제 모음이 아니라, 로봇 시스템에서 반복적으로 사용할 수 있는 임베디드 제어 구조를 만드는 것을 목표로 합니다.

상위 컴퓨터와 하위 제어기의 역할을 다음과 같이 분리합니다.

```text
Raspberry Pi
→ AI, 음성 처리, 행동 결정 및 상위 명령 생성

STM32F411CEU6
→ 실시간 액추에이터, 센서 및 입출력 장치 제어
```

향후 SLAM, 자율주행 및 AI 로봇 시스템에서 생성된 상태와 명령을 실제 로봇 하드웨어 동작으로 연결할 수 있는 하위 제어 시스템으로 확장할 계획입니다.

---

## Development Log

PetBot의 아이디어 구상, 외형 설계, 3D 모델링, 하드웨어 구성, 펌웨어 개발 및 소프트웨어 연동 과정은 아래 개발 홈페이지에 정리하고 있습니다.

- Website: [https://goldenboy.co.kr](https://goldenboy.co.kr)
- Section: **PetBot**
