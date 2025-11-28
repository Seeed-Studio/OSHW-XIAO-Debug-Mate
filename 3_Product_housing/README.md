# 🏠 Product Housing

This directory contains 3D printable enclosure files for the XIAO Debug Mate.

## 📁 Files Included

| File | Description | Dimensions |
|------|-------------|------------|
| `Debugger Upper Housing` | Top shell of the enclosure | 100 × 57 × 11 mm |
| `Debugger Lower Housing` | Bottom shell of the enclosure | 100 × 58 × 12.2 mm |
| `Debugger Screen Mounting Block` | TFT display mount bracket | 57.5 × 47.5 × 6.4 mm |
| `Debugger Keycap` | Rotary encoder button cap | 16.8 × 6.4 × 5 mm |
| `Bambu_Studio_XIAO_Debug_Mate.3mf` | Pre-configured Bambu Studio project |

## 🖨️ Printing Recommendations

### Material
- **Recommended:** ABS (Acrylonitrile Butadiene Styrene)
- **Alternative:** PETG, ASA
- **Not Recommended:** PLA (may warp with heat from electronics)

### Color Scheme
| Part | Recommended Color |
|------|-------------------|
| Upper Housing | Black |
| Lower Housing | Black |
| Screen Mount | Black |
| Keycap | Green (for visibility) |

### Print Settings

| Parameter | Value |
|-----------|-------|
| Layer Height | 0.2 mm |
| Infill | 20-30% |
| Wall Loops | 3 |
| Top/Bottom Layers | 4 |
| Supports | Yes (for housing parts) |

### Orientation Guide

```
Upper Housing:
  └── Print with the outer surface facing up
      (supports needed for internal features)

Lower Housing:
  └── Print with the outer surface facing down
      (supports needed for screw posts)

Screen Mount:
  └── Print flat on the build plate
      (minimal supports needed)

Keycap:
  └── Print with the top surface facing up
      (no supports needed)
```

## 🔧 Post-Processing

### Required Steps

1. **Remove Supports**
   - Carefully remove all support material
   - Use pliers for hard-to-reach areas

2. **Deburring**
   - Remove any sharp edges or protrusions
   - Sand connection points for smooth fit
   - Focus on areas where parts mate together

3. **Test Fit**
   - Verify PCB fits in lower housing
   - Check screen alignment with mount
   - Ensure buttons operate freely

### Optional Finishing

- **Sanding:** 220-400 grit for smooth surface
- **Acetone Vapor Smoothing:** For ABS parts only
- **Paint:** Acrylic or spray paint for custom colors

## 📐 Assembly Order

```
1. Install screen in mounting block
         │
         ▼
2. Mount PCB in lower housing
         │
         ▼
3. Attach screen assembly
         │
         ▼
4. Place keycap on encoder
         │
         ▼
5. Close with upper housing
         │
         ▼
6. Secure with screws
```

## 🔩 Hardware Required

| Item | Quantity | Specification |
|------|----------|---------------|
| Self-tapping screws | 4 | M2 × 6mm |
| Screen mounting screws | 4 | M2 × 4mm |

## 📦 Using Bambu Studio

The included `.3mf` file contains pre-configured settings:

1. Open `Bambu_Studio_XIAO_Debug_Mate.3mf` in Bambu Studio
2. Select your printer profile
3. Adjust settings if needed
4. Slice and print

**Note:** Settings are optimized for Bambu Lab printers but can be adapted for other printers.

## 🎨 Customization

The STEP (.stp) files can be modified in CAD software:

- **Fusion 360** - Import STEP, modify, export STL
- **SolidWorks** - Open STEP directly
- **FreeCAD** - Import STEP (open-source option)
- **Onshape** - Import STEP (browser-based)

### Common Modifications

- Add ventilation holes
- Customize button height
- Add mounting points
- Engrave logo or text

## ⚠️ Important Notes

1. **Tolerances:** Printed parts may need slight adjustment for fit
2. **Shrinkage:** ABS shrinks ~0.5-0.8% - account for this if modifying
3. **Heat:** Ensure adequate ventilation; electronics generate heat during operation
4. **Connectors:** Verify USB-C and debug connector clearances after printing

## 📸 Preview

```
     ┌────────────────────────────┐
     │    ╔══════════════════╗    │
     │    ║                  ║    │
     │    ║    TFT Display   ║    │
     │    ║                  ║    │
     │    ╚══════════════════╝    │
     │                        ○   │  ← Keycap
     │   ○  USB-C      Debug ○   │
     └────────────────────────────┘
          XIAO Debug Mate
```

