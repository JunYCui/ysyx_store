#!/usr/bin/env python3
import random
def write_hex_file(filename, num_values=10, bits=32):
    """
    生成随机的 32 位十六进制数据，并写入文件（每行一个数据）
    
    参数:
        filename (str): 输出文件名(如 "data.hex")
        num_values (int): 生成的数据数量（默认 10 个）
        bits (int): 数据位宽（默认 32 位）
    """
    max_val = (1 << bits) - 1  # 计算最大值（如 32 位 = 0xFFFF_FFFF）
    
    with open(filename, 'w') as f:
        for _ in range(num_values):
            # 生成随机 32 位数据（十六进制）
            value = random.randint(0, max_val)
            # 写入文件，格式化为 8 字符宽的十六进制（补零对齐）
            f.write(f"{value:08X}\n")  
if __name__ == "__main__":
    output_file = "./data/rom.hex"  # 输出文件名
    write_hex_file(output_file, num_values=50)  # 生成 20 个数据
    
    print(f"✅ 已生成 {output_file}，包含 50 个 32 位十六进制数据！")