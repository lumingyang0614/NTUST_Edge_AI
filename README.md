# NTUST_Edge_AI
NTUST Edge AI (111-02) 期末專題報告

分為兩部份檔案 
- Python部份進行資料收集、模型訓練
	-	getdata.ipynb 
		- 天氣資料收集並儲存為data.csv
	- 	tinyML.ipynb 
		- 模型訓練，並將獲得模型model.h移動至Nano_33_ble_v2與Arduino_weather_predict_forecast.ino 同樣路徑
		- 實作以Colab進行訓練 (連結)[https://colab.research.google.com/drive/1XH94nDZ3qSLPDQXr3QBTD14mm0TF8bsb#scrollTo=6b7d2931]

Nano_33_ble_v2部份進行預測
	-	Arduino® Nano 33 BLE Sense Rev2 實作
	-	需下載Arduino_LPS22HB 及 Arduino_HS300x
	-	驗證上傳即可，因為實作以過去10秒作為輸入設定，驗證上傳完成後需等待一下，開啟監控視窗即可看到感測資料與預測結果。


![](https://hackmd.io/_uploads/rkAwuGY8n.png)

