from pathlib import Path

data = Path("_BHMEA2024.rdb.extracted")

print("options(error=recover)")
for file in data.iterdir():
    if not file.is_file(): continue

    size = file.stat().st_size
    print(f'lazyLoadDBfetch(c(0L,{size}L), "/home/rivit/Downloads/_BHMEA2024.rdb.extracted/{file.name}", 0, NULL)')
    print(f"print('{'-'*30}')")