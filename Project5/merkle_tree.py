import hashlib
def merkle_tree(leaves):
    tree = [list(map(lambda x: hashlib.sha256(x.encode()).hexdigest(), leaves))]
    print("测试值为：",data)
    print("哈希值分别为：", tree)
    while len(tree[-1]) > 1:
        level = []
        for i in range(0, len(tree[-1]), 2):
            if i + 1 == len(tree[-1]):
                level.append(tree[-1][i])
            else:
                level.append(hashlib.sha256((tree[-1][i] + tree[-1][i + 1]).encode()).hexdigest())
        tree.append(level)
    return tree

data = ["merkle", "tree", "leaves", "tree"]
tree = merkle_tree(data)
print("所建立的merkle tree：", tree)
root_hash = tree[-1][0]
print("根节点哈希值为：", root_hash)
