from PIL import Image
import sys

def convert_image_to_2bpp(image_path, output_path):
    image = Image.open(image_path).convert("RGB")
    pixels = list(image.getdata())
    
    # Detectar as 4 cores únicas
    unique_colors = []
    for color in pixels:
        if color not in unique_colors:
            unique_colors.append(color)
        if len(unique_colors) > 4:
            raise ValueError("A imagem tem mais de 4 cores! 2bpp suporta apenas 4.")

    # Criar mapeamento: RGB -> índice (0-3)
    color_to_index = {color: i for i, color in enumerate(unique_colors)}

    # Converter os pixels para índices
    indices = [color_to_index[p] for p in pixels]

    # Empacotar os índices 2bpp em bytes (4 pixels por byte)
    packed = []
    for i in range(0, len(indices), 4):
        byte = 0
        for j in range(4):
            if i + j < len(indices):
                byte |= (indices[i + j] & 0x03) << (6 - j * 2)
        packed.append(byte)

    # Escrever no arquivo .c
    with open(output_path, "w") as f:
        f.write("const uint8_t imageData[] = {\n    ")
        for i, byte in enumerate(packed):
            f.write(f"0x{byte:02x}, ")
            if (i + 1) % 40 == 0:
                f.write("\n    ")
        f.write("\n};\n")

    print("Paleta detectada (RGB):")
    for i, color in enumerate(unique_colors):
        print(f"Índice {i}: {color}")


# Exemplo de uso
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Uso: python converter.py imagem.png [variavel opcional] [saida.h opcional]")
    else:
        image_path = sys.argv[1]
        var_name = sys.argv[2] if len(sys.argv) >= 3 else "imageData"
        output_path = sys.argv[3] if len(sys.argv) >= 4 else "output.h"
        convert_image_to_2bpp(image_path, output_path)