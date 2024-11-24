def compare_files_line_by_line(file1, file2):
    idx = 1
    with open(file1, 'r', encoding='utf-8') as f1, open(file2, 'r', encoding='utf-8') as f2:
        for line1, line2 in zip(f1, f2):
            if line1 != line2:
                print(f"error in line {idx}")
                return False
            idx += 1
    return True

file1 = "key_query_out1.txt"
file2 = "key_query_ans1.txt"
result = compare_files_line_by_line(file1, file2)
print("兩個檔案是否相同:", result)