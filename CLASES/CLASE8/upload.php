<?php
// Ruta donde se guardará la imagen
$uploadDir = 'C:\ardu24\xampp\htdocs\dashboard\DATOS\FOTO';  // Ruta completa en el servidor

// Obtener los datos JSON de la solicitud POST
$data = file_get_contents("php://input");

// Decodificar el JSON recibido
$imageData = json_decode($data, true);

// Verificar si la clave 'imageData' está presente en el JSON
if (isset($imageData['imageData'])) {
    // Obtener la imagen codificada en Base64
    $base64Image = $imageData['imageData'];

    // Eliminar el prefijo 'data:image/jpeg;base64,' de la cadena Base64
    $base64Image = str_replace('data:image/jpeg;base64,', '', $base64Image);

    // Decodificar la imagen
    $image = base64_decode($base64Image);

    // Generar un nombre único para la imagen
    $imageName = 'captura_' . time() . '.jpg';
    $filePath = $uploadDir . $imageName;

    // Guardar la imagen en el servidor
    if (file_put_contents($filePath, $image)) {
        echo "Imagen recibida y guardada como $imageName";
    } else {
        echo "Error al guardar la imagen";
    }
} else {
    echo "No se recibió imagen válida";
}
?>
