import numpy as np
import joblib
from tensorflow.keras.models import load_model

import os

print("当前工作目录:", os.getcwd())

# 加载模型和缩放器
input_scaler = joblib.load('e:\Learning\control\walking_assist\src\strategy\scripts\model\input_scaler.save')
output_scaler = joblib.load('e:\Learning\control\walking_assist\src\strategy\scripts\model\output_scaler.save')
trained_model = load_model('e:\Learning\control\walking_assist\src\strategy\scripts\model\\neural_network_model.keras')

def predict_output(input_sample):
    """
    使用训练好的模型进行预测，并将输出四舍五入为整数。

    参数：
    input_sample (list): 输入数据，列表形式，长度与训练模型时一致。

    返回：
    np.ndarray: 预测输出，四舍五入为整数后的值。
    """
    # 对输入数据进行归一化
    input_scaled = input_scaler.transform([input_sample])

    # 使用模型预测
    predicted_scaled_output = trained_model.predict(input_scaled, verbose=0)

  
    # 将归一化的输出反归一化
    predicted_output = output_scaler.inverse_transform(predicted_scaled_output)

    # 对输出进行四舍五入
    rounded_output = np.round(predicted_output).astype(int)

    return rounded_output

if __name__ == "__main__":
    # 示例输入
    input_sample = [34, 50, 60, 150]  # 替换为实际的输入数据
    output = predict_output(input_sample)
    print(f"给定输入 {input_sample} 的预测输出: {output}")
