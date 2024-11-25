## Install Docker ##
```
sudo apt update
sudo apt install apt-transport-https ca-certificates curl software-properties-common
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
sudo apt update
sudo apt install docker-ce
sudo systemctl enable docker
sudo systemctl start docker
```

## Build Docker ##
```
sudo docker build -t ros2-foxy-workspace .
```

## Run Docker ##
```
sudo docker run -it ros2-foxy-workspace
```

## Make it run during reboot ##
```
sudo docker run -d --restart unless-stopped ros2-foxy-workspace
```

## Check Docker ##
```
sudo docker ps
```

## Stop Docker ##
```
sudo docker stop <CONTAINER ID>
```

## Cancel auto run after reboot ##
```
sudo docker run -d --restart=no ros2-foxy-workspace
```
