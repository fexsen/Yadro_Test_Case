import threading

# Функция вычисления пропускной способности
def process_file(filename):
    with open(filename, 'r') as file:
        imsi1_sum = 0
        imsi1_count = 0
        imsi2_sum = 0
        imsi2_count = 0
        for line in file:
            data = line.split()
            if data[3] == '1':
                imsi1_sum += float(data[9])
                imsi1_count += 1
            elif data[3] == '2':
                imsi2_sum += float(data[9])
                imsi2_count += 1
        if imsi1_count > 0:
            imsi1_avg = imsi1_sum / imsi1_count
            print(f"{filename[0:2]} IMSI 1: {imsi1_avg * 8 / 1000}")
        if imsi2_count > 0:
            imsi2_avg = imsi2_sum / imsi2_count
            print(f"{filename[0:2]} IMSI 2: {imsi2_avg * 8 / 1000}")


if __name__ == "__main__":
    # Имена двух файлов
    filename1 = "UlRlcStats.txt"
    filename2 = "DlRlcStats.txt"

    # Создание экземпляров потоков для параллельного вычисления из двух файлов
    t1 = threading.Thread(target=process_file, args=(filename1,))
    t2 = threading.Thread(target=process_file, args=(filename2,))

    # Запуск потоков
    t1.start()
    t2.start()

    # Ожидание завершения потоков
    t1.join()
    t2.join()