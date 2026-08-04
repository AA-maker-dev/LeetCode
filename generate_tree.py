from pathlib import Path

ROOT = Path(".")

IGNORE = {
    ".git",
    ".github",
    "__pycache__",
    ".vscode",
}

folders = sorted(
    [
        p.name
        for p in ROOT.iterdir()
        if p.is_dir() and p.name not in IGNORE
    ]
)

tree = "```\nLeetCode/\n"

for i, folder in enumerate(folders):
    connector = "└──" if i == len(folders) - 1 else "├──"
    tree += f"{connector} {folder}/\n"

tree += "```\n"

readme = Path("README.md").read_text()

start = "<!-- TREE_START -->"
end = "<!-- TREE_END -->"

before = readme.split(start)[0] + start + "\n"
after = "\n" + end + readme.split(end)[1]

Path("README.md").write_text(before + tree + after)

print("README updated.")