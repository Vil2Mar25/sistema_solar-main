# Trabalho Final de Computação Gráfica

Sistema Solar utilizando OpenGL

### 1. Link do vídeo de demonstração:

Link do vídeo no YouTube: https://youtu.be/IBWRCkLx6uY

### 2. Descrição do trabalho:

O presente trabalho tem como intuito criar um Sistema Solar, contando com o Sol e os demais 8 planetas (Mercúrio, Vênus, Terra, Marte, Júpiter, Saturno, Urano e Netuno).

Além de exibir o Sistema Solar, o projeto também possui as animações de rotação e de translação dos planetas ao redor do Sol, para tanto é necessário que o usuário de um clique na tela para que seja ativado os movimentos.

Para a realização deste trabalho, foi necessário a criação de figuras e de transformações geométricas, além da aplicação de texturas e de animações. Por fim, também foi incluído a iluminação nos planetas e no Sol, por meio da biblioteca "stb_image.h".

### 3. Execução:

- Uma vez que o projeto é rodado, uma janela exibe o Sistema Solar de maneira estática.

<img src="https://user-images.githubusercontent.com/58275584/179322529-80ce9b32-4352-4c74-83c5-00ce435b4d87.png"  width="800" height="300" />

- Ao pessionar clicar com o mouse na tela, é dado início as animações de rotação e translação. Para interromper a animação, basta clicar novamente na tela.

<img src="https://user-images.githubusercontent.com/58275584/179322600-31cf4775-31bd-403d-8aa2-919dfea54d4e.png"  width="800" height="300" />

### 4. Dificuldades:

As dificuldades começaram já durante a configuração da IDE e na instalação e execução das bibliotecas necessárias, uma vez que elas sempre davam erro durante a depuração. Contudo, após muitas tentativas e tutoriais assistidos, conseguimos fazê-las funcionar e então foi possível construir o projeto em questão. Outra questão foi como aplicar a textura nos planetas e como fazer as animações, todavia esses problemas foram solucionados após pesquisar na internet e no livro LearnOpenGL como realizar os mesmos. Na parte final do trabalho, onde a iluminação deveria ser aplicada, a maior dificuldade foi em compreender como a biblioteca funcionava e como implementá-la no nosso script, porém, após muita pesquisa de toda a equipe, foi possível implementar a iluminação no nosso projeto.

### 5. Avanços:

Desde o início do projeto nos deparamos com diversas difculdades, desde a instalação das bibliotecas até na construção do script. Porém, com tempo, e MUITOS tutoriais, conseguimos executar as bibliotecas e escrever o código que criasse o Sistema Solar, junto com suas texturas e animações. Já quanto a parte 2 do trabalho, incluir a biblioteca responsável pela iluminação não foi um problema, uma vez que já havíamos compreendido como fazer tal processo, porém entender como ela funcionava e implementar ela no nosso projeto foi um pouco mais desafiador e requereu mais tempo e pesquisa da equipe, mas no fim conseguimos implementá-la.

### 6. Contribuição de cada membro da equipe:

Francisco Roni / Francisco Vilmar - Criação dos planetas e iluminação

Françueudes Pereira / Guilherme Alves - Aplicação das texturas e iluminação

Iara Costa de Oliveira / Igor César Almeida da Costa / Igor Maciel de Sousa - Aplicação das animações e iluminação

### 7. Recursos utilizados:

[Visual Studio](https://visualstudio.microsoft.com/pt-br/vs/) - IDE utilizada para a criação desse projeto.

[OpenGL](https://www.opengl.org/) - Utilizado para criar a computação gráfica e o processamento de elementos em 3D.

[GLEW](http://glew.sourceforge.net/) - Usado para o carregamento de extensões do C++, linguagem de programação usada nesse projeto.

[GLAD](https://glad.dav1d.de/) - Usado para definir e carregar todas as funções relevantes do OpenGL de acordo com a versão.

[GLFW](https://www.glfw.org/)/[GLUT](https://www.opengl.org/resources/libraries/glut/glut_downloads.php) - Utilizado na criação de janelas, contextos e superfícies, e também no tratamento de eventos de entrada por parte do usuário.

[stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) - Utilizado para a aplicação de iluminação no projeto.

[Livro LearnOpenGL](https://learnopengl.com/) - Usado como fonte de pesquisa.

### 8. Integrantes da Equipe 3:

- Francisco Roni de Sousa Melo - 404758
- Francisco Vilmar Rodrigues da Silva - 394089
- Françueudes Pereira de Abreu - 400379
- Guilherme Alves Pereira - 420868
- Iara Costa de Oliveira - 497166
- Igor César Almeida da Costa - 414719
- Igor Maciel de Sousa - 385146