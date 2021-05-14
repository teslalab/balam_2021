# Proyecto Balam 2021

## Guia de Instalación de Tarjeta ESP32 en Arduino IDE
### Pasos A Seguir:
1. Instalar Arduino IDE (no usar el zip)
2. Abrir ARDUINO IDE
3. Debemos ir a la pestaña ***Archivo***->***Preferencias***.
	- En la pestaña ***Ajustes*** buscamos la opción: ***Gestor de URLs Adicionales de Tarjetas: ***
	- Pegamos la siguiente URL: `https://dl.espressif.com/dl/package_esp32_index.json`
	- Luego precionamos la opción ***OK*** y automaticamente se cerrara la ventana.
4. Debemos ir a la pestaña ***Herramientas***->***Placa***->***Gestor de tarjetas***.
	- Colocamos en la barra de busqueda ***ESP32***.
	- Seleccionamos la opción que nos muestre ***esp32***.
	- Instalamos y luego precionamos la opción de ***Cerrar***.

Con esto tendremos completa la instalación de nuestra tarjeta ESP32 y lista para ser programada.	
![Arduino Settings](arduino_settings.png)

5. Instalar el módulo del ESP32 en el gestor de tarjetas.

### Instalación USB Driver ***(Si no reconoce el puerto COM)***

En algunos casos nuestra PC no es capaz de reconocer el dispositivo USB que nosotros conectamos, es por ello que dejaremos un archivo para la instalación del driver con ello nuestra PC deberá ser capaz de reconocer el dispositivo conectado, en caso de que el problema persista asegúrese de que su dispositivo no se este sobre calentando.

[Descarga este driver para Windows][DRIVER_USB]

[DRIVER_USB]: https://drive.google.com/file/d/1yuZ91mJfR12bhASqD9ffsebzsEOJz8Om/view?usp=sharing

1. Descomprimir el archivo ZIP descargado 
2. Seleccionar el archivo dependiendo de nuestra instalación de Windows
	- Para 32 Bits `CP210xVCPInstaller_x86`
	- Para 64 Bits `CP210xVCPInstaller_x64`
3. Brindar permisos de Administrador	
4. Click en la opción ***Siguiente***
5. Click en la opción ***Finalizar***
