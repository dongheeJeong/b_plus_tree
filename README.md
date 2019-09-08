# b_plus_tree
generate b+ tree images using [DOT (graph description language)](https://en.wikipedia.org/wiki/DOT_(graph_description_language)).
make dot file and execute dot command for creating b+ tree image from .dot file.

## Features
*   Inserting Integer values


## What's missing
*   Removeing inserted value

## Usage
```text
[donghee:~/Git/b_plus_tree]$ ./b+tree
```
```text
================================================================================
for inserting a key, input positive key.
for  deleting a key, input negative value of key.
curent elements: []
================================================================================
input: 1 2 3 4 5
```
```text
================================================================================
for inserting a key, input positive key.
for  deleting a key, input negative value of key.
curent elements: [1 2 --> 3 4 5 --> ]
2019-9-8-130245776405.png generated.
================================================================================
input: 
```
```text
================================================================================
for inserting a key, input positive key.
for  deleting a key, input negative value of key.
curent elements: [1 2 --> 3 4 5 --> ]
2019-9-8-130245776405.png generated.
================================================================================
input: 6 7 8 9
```
```text
================================================================================
for inserting a key, input positive key.
for  deleting a key, input negative value of key.
curent elements: [1 2 --> 3 4 --> 5 6 --> 7 8 9 --> ]
2019-9-8-130427821041.png generated.
================================================================================
input: 
```
```text
[donghee:~/Git/b_plus_tree]$ ls image
2019-9-8-125056580132.png  2019-9-8-125056679295.png  2019-9-8-130050348144.png  2019-9-8-130050448010.png
2019-9-8-125056597504.png  2019-9-8-125056714133.png  2019-9-8-130050365761.png  2019-9-8-130050483129.png
...
```



## INSTALL
### Dependency package: Graphviz
#### Arch
```text
sudo pacman -S graphviz
```
#### Ubuntu
```text
sudo apt-get install graphviz
```
#### Centos
```text
sudo yum install graphviz
```

### Install
```text
git clone https://github.com/dongheejeong/b_plus_tree.git
cd b_plus_tree
make
```
