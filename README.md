🛠️ Funcionalidades
🔐 Gestión de Usuarios

    Inicio de sesión: Permite a los usuarios ingresar con su nombre y contraseña, verificando la información en la base de datos.
    Cierre de sesión: Limpia los datos de sesión y redirige al usuario al menú principal.
    Registro de usuarios: (Implementado en otras partes del sistema) Permite crear un nuevo usuario.

💬 Gestión de Conversaciones y Comentarios

    Creación de conversaciones: Los usuarios pueden iniciar nuevos temas de discusión.
    Comentarios: Dentro de cada conversación, los usuarios pueden agregar comentarios y responder a otros participantes.

📊 Estadísticas

    Muestra datos sobre:
        Total de usuarios registrados.
        Número de conversaciones creadas.
        Actividad general de los usuarios.

🗄️ Interacción con la Base de Datos

    Consulta de usuarios: Recupera información detallada de los usuarios desde la base de datos.
    Validación de credenciales: Verifica la combinación de nombre y contraseña para autenticar usuarios.
    Comprobación de nombres: Determina si un nombre ya está registrado.
    
1️⃣ Requisitos

    Sistema operativo: Windows (por el uso de <winsock2.h>).
    Compilador: GCC o equivalente compatible con C++.
    Base de datos: SQLite3 configurada con las tablas necesarias.
    Servidor: Configurado para manejar comunicación mediante sockets.
