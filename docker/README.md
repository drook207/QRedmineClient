# Redmine in Docker

Launching a Redmine instance on your localhost using docker compose.
For further information see [Redmine-Docker](https://hub.docker.com/_/redmine).

## Compose the containers

``` bash
docker-compose -f docker-redmine.yml up
```

Run this command and wait until redmine is ready

## Connect to redmine on localhost

In your browser connect to [localhost](http://localhost:8080).

## Login to redmine

The default credentials are:

- Username: admin
- Password: admin

You can create new users, register new users, create project etc.
For further information see [Redmine](https://www.redmine.org/).
