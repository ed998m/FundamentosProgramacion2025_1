// Importa las bibliotecas necesarias
using UnityEngine;
using System.IO.Ports; // Para comunicación serial con Arduino u otro microcontrolador
using System.Collections.Generic; // Para usar listas (List<>)

public class CONSOLA : MonoBehaviour
{
    // Sección de configuración para la conexión serial
    [Header("Configuración Serial")]
    public string portName = "COM3"; // Nombre del puerto
    public int baudRate = 115200;    // Velocidad de transmisión de datos
    private SerialPort serialPort;   // Objeto que maneja la conexión serial

    // Objeto que se va a rotar según los datos recibidos
    [Header("Objeto a Rotar")]
    public GameObject targetObject;

    // Variables para almacenar los valores de orientación y aceleración
    private float roll, pitch, yaw;
    private float accelX, accelY, accelZ;
    private float voltage;

    // Historial de los datos para graficar
    private List<float> rollHistory = new List<float>();
    private List<float> pitchHistory = new List<float>();
    private List<float> yawHistory = new List<float>();
    private List<float> accelXHistory = new List<float>();
    private List<float> accelYHistory = new List<float>();
    private List<float> accelZHistory = new List<float>();
    private const int historyLength = 100; // Cantidad máxima de datos almacenados en el historial

    // Textura blanca usada para dibujar líneas en la interfaz
    private static Texture2D _whiteTexture;
    private static Texture2D WhiteTexture {
        get {
            if (_whiteTexture == null) {
                _whiteTexture = new Texture2D(1, 1); // Crea una textura de 1x1
                _whiteTexture.SetPixel(0, 0, Color.white); // Píxel blanco
                _whiteTexture.Apply(); // Aplica los cambios a la textura
            }
            return _whiteTexture;
        }
    }

    // Se ejecuta al iniciar el script
    void Start()
    {
        // Inicializa el puerto serial con configuración
        serialPort = new SerialPort(portName, baudRate) { ReadTimeout = 100 };
        try {
            serialPort.Open(); // Intenta abrir el puerto
            Debug.Log("Conectado al puerto: " + portName);
        } catch (System.Exception e) {
            Debug.LogError("Error al abrir puerto: " + e.Message); // Muestra error si no puede conectar
        }
    }

    // Se ejecuta una vez por frame
    void Update()
    {
        if (!serialPort.IsOpen) return; // Si el puerto no está abierto, no hace nada

        try {
            string data = serialPort.ReadLine(); // Lee una línea de datos del puerto serial
            ParseData(data); // Interpreta los datos leídos
            UpdateHistory(); // Actualiza el historial de datos
        } catch {
            // Si hay un error en la lectura, simplemente lo ignora
        }

        // Aplica rotación al objeto objetivo si está asignado
        if (targetObject != null)
            targetObject.transform.rotation = Quaternion.Euler(pitch, yaw, roll);
    }

    // Procesa los datos recibidos del puerto serial
    void ParseData(string data)
    {
        string[] parts = data.Split('|'); // Divide el string por el carácter "|"
        foreach (string part in parts)
        {
            // Cada dato viene con un prefijo (ej: R=, P=, etc.). Se extrae el valor numérico.
            if (part.StartsWith("R=")) roll = ParseFloat(part.Substring(2));
            else if (part.StartsWith("P=")) pitch = ParseFloat(part.Substring(2));
            else if (part.StartsWith("Y=")) yaw = ParseFloat(part.Substring(2));
            else if (part.StartsWith("AX=")) accelX = ParseFloat(part.Substring(3));
            else if (part.StartsWith("AY=")) accelY = ParseFloat(part.Substring(3));
            else if (part.StartsWith("AZ=")) accelZ = ParseFloat(part.Substring(3));
            else if (part.StartsWith("V=")) voltage = ParseFloat(part.Substring(2));
        }
    }

    // Convierte una cadena a número flotante con formato internacional (punto decimal)
    float ParseFloat(string value)
    {
        float.TryParse(value, System.Globalization.NumberStyles.Float, System.Globalization.CultureInfo.InvariantCulture, out float result);
        return result;
    }

    // Agrega los valores actuales al historial y mantiene el tamaño máximo
    void UpdateHistory()
    {
        rollHistory.Add(roll);
        pitchHistory.Add(pitch);
        yawHistory.Add(yaw);
        accelXHistory.Add(accelX);
        accelYHistory.Add(accelY);
        accelZHistory.Add(accelZ);

        // Si se pasa del límite, elimina el dato más antiguo
        if (rollHistory.Count > historyLength)
        {
            rollHistory.RemoveAt(0);
            pitchHistory.RemoveAt(0);
            yawHistory.RemoveAt(0);
            accelXHistory.RemoveAt(0);
            accelYHistory.RemoveAt(0);
            accelZHistory.RemoveAt(0);
        }
    }

    // Dibuja la interfaz gráfica en pantalla
    void OnGUI()
    {
        // Muestra los valores actuales de orientación, aceleración y voltaje
        GUI.Label(new Rect(10, 10, 400, 20), $"Roll: {roll:F1}° | Pitch: {pitch:F1}° | Yaw: {yaw:F1}°");
        GUI.Label(new Rect(10, 30, 400, 20), $"Acelerómetro: X={accelX:F2}g | Y={accelY:F2}g | Z={accelZ:F2}g");
        GUI.Label(new Rect(10, 50, 200, 20), $"Voltaje: {voltage:F2}V");

        // Dibuja las gráficas históricas de cada variable
        DrawGraph(rollHistory, Color.red, "Roll (Ángulo)", new Rect(10, 80, 300, 60), -180f, 180f);
        DrawGraph(pitchHistory, Color.green, "Pitch (Ángulo)", new Rect(10, 150, 300, 60), -180f, 180f);
        DrawGraph(yawHistory, Color.blue, "Yaw (Ángulo)", new Rect(10, 220, 300, 60), -180f, 180f);
        DrawGraph(accelXHistory, Color.cyan, "Acel X (g)", new Rect(10, 290, 300, 60), -2f, 2f);
        DrawGraph(accelYHistory, Color.magenta, "Acel Y (g)", new Rect(10, 360, 300, 60), -2f, 2f);
        DrawGraph(accelZHistory, Color.yellow, "Acel Z (g)", new Rect(10, 430, 300, 60), -2f, 2f);
    }

    // Dibuja una gráfica de línea con los datos históricos
    void DrawGraph(List<float> data, Color color, string title, Rect area, float min, float max)
    {
        GUI.Box(area, GUIContent.none); // Caja base de la gráfica
        GUI.Label(new Rect(area.x, area.y - 20, area.width, 20), title); // Título arriba

        // Dibuja línea horizontal para el valor cero si está dentro del rango
        if (min < 0 && max > 0)
        {
            float zeroY = area.y + area.height - Mathf.InverseLerp(min, max, 0) * area.height;
            DrawLine(new Vector2(area.x, zeroY), new Vector2(area.x + area.width, zeroY), Color.gray, 1);
        }

        // Dibuja línea conectando los puntos del historial
        if (data.Count > 1)
        {
            float step = area.width / (historyLength - 1);
            for (int i = 1; i < data.Count; i++)
            {
                float x1 = area.x + (i - 1) * step;
                float y1 = area.y + area.height - Mathf.InverseLerp(min, max, Mathf.Clamp(data[i - 1], min, max)) * area.height;
                float x2 = area.x + i * step;
                float y2 = area.y + area.height - Mathf.InverseLerp(min, max, Mathf.Clamp(data[i], min, max)) * area.height;
                DrawLine(new Vector2(x1, y1), new Vector2(x2, y2), color, 2);
            }
        }
    }

    // Dibuja una línea entre dos puntos en pantalla con un color y grosor especificado
    void DrawLine(Vector2 start, Vector2 end, Color color, int thickness)
    {
        if (thickness <= 0) return;

        GUI.color = color;
        Vector2 direction = end - start;
        float angle = Mathf.Atan2(direction.y, direction.x) * Mathf.Rad2Deg;
        GUIUtility.RotateAroundPivot(angle, start);
        GUI.DrawTexture(new Rect(start.x, start.y - thickness / 2, direction.magnitude, thickness), WhiteTexture);
        GUIUtility.RotateAroundPivot(-angle, start);
        GUI.color = Color.white;
    }

    // Cierra el puerto serial al cerrar la aplicación o destruir el objeto
    void OnDestroy()
    {
        if (serialPort?.IsOpen == true)
            serialPort.Close();
    }
}
