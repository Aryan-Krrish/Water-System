# 🌱 **Water-System**
**Système de surveillance intelligente pour plantes**

## 🎯 **À quoi ça sert**
**Water-System** surveille automatiquement vos plantes et agit en conséquence :  
- **Humidité** : active un moteur/pompe si sol trop sec  
- **Lumière** : détecte jour/nuit (LED indicateur)  
- **Distance** : capteur ultrasonique + alarme (buzzer) si trop près  
- **Contrôle total** via **Bluetooth HC-05** (app mobile)

**Utilisations parfaites** :  
- 🌿 **Serre intelligente** (arrosage auto)  
- 🏠 **Plantes d'intérieur** (surveillance jour/nuit)  
- 📱 **Contrôle à distance** (vacances)  
- 🎓 **Projet éducatif** (électronique + botanique)

---

## 🛠️ **Matériel requis**
Arduino UNO/Nano/Mega

Capteur humidité sol (A0)

LDR lumière (A2)

Capteur ultrasonique Grove (A3)

Moteur/pompe + transistor (pin 9)

2 LEDs (moteur ON/OFF : pins 3,4)

Buzzer (pin 13)

LED jour/nuit (pin 6)

Module Bluetooth HC-05 (Serial1)

---

## 📚 **Bibliothèques Arduino**
**❌ Aucune bibliothèque requise !**  
Code **100% natif Arduino** (`tone()`, `pulseIn()`, `Serial1`)

---

## 🔌 **Drivers Arduino/ESP (bonus)**
🇨🇳 **[WCH.cn - Drivers CH340/CH341](http://www.wch.cn/downloads/CH341SER_EXE.html)**  
**Téléchargez** : `CH341SER.EXE` (Windows/Mac/Linux) [web:6]

CH340 → WCH.cn (AliExpress standard)

CP2102 → https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers

---

## 🚀 **Installation**
1. **Branchez** tous les capteurs selon schéma
2. **Téléchargez** : `SmartPlantGuardian.ino`
3. **Upload** sur Arduino
4. **Serial Monitor** (9600 bauds) : `Humidity Light Distance`

---

## 📱 **Commandes Bluetooth HC-05**
MOTEUR (pompe/arrosage) :

'1' → Moteur ON

'2' → Moteur OFF

'3' → Auto (humidité)

LUMIÈRE :

'4' → LED jour/nuit ON

'5' → LED jour/nuit OFF

'6' → Auto (LDR)

BUZZER :

'7' → Buzzer ON continu

'8' → Buzzer OFF

'9' → Auto (distance)

Données envoyées : "H:350 L:620 D:25cm"

---

## 🧠 **Logique automatique**
✅ HUMIDITÉ < 200 → Moteur ON (arrosage)
✅ LUMIÈRE > 600 → LED "Jour" ON
✅ DISTANCE < 50cm → Buzzer aléatoire (anti-vol/intrus

**Seuils réglables** dans le code :
```cpp
humidityThresholdLow = 200;  // Sol sec
humidityThresholdHigh = 400; // Sol humide
lightThreshold = 600;        // Lumière jour
📊 Sortie Serial (debug)
text
Humidity: 180
Distance: 42.3 cm
Light: 750
Received command: 1
⚠️ Conseils utilisation
Calibrez les seuils selon vos capteurs

Alimentation stable pour le moteur (batterie externe)

App Bluetooth : toute app série (Serial Bluetooth Terminal)

✨ Améliorations possibles
Écran LCD : affichage valeurs

ESP32 WiFi : notifications Telegram

Relais : vraie pompe à eau

RTC : arrosage horaire
