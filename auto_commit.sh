#!/bin/bash

# Kiểm tra xem có thay đổi nào trong thư mục không
if [[ -n $(git status -s) ]]; then
    echo "tu dong commit..."
    git add .
    timestamp=$(date "+%Y-%m-%d %H:%M:%S")
    git commit -m "Auto-commit: Cap nhat code luc $timestamp"
    git push origin main
    echo "Da tu dong day code len GitHub thanh cong!"
else
    echo "Khong co thay doi nao moi."
fi