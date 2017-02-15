# Aura Launcher's Website
### How to setup locally
##### Setup System
 - Install [npm][nodejs] (Included with nodejs)
 - Install Bower and Grunt:
`sudo npm install -g bower grunt-cli`

##### Initialize Dependencies
```
npm install
bower install
```
##### Launch Website Locally
```
grunt
```
You should now be able to navigate to `127.0.0.1:4000` in a browser to view the page locally. It will automatically refresh the page when any files are modified.

### How to deploy to the website
If you've been given direct repository access you can follow these steps to update the gh-pages branch with the website-source branch:
 - Install [RubyGems][ruby-gems].
 - Install rake: `gem install rake`

Once the system is setup all you have to do is: `rake deploy`

[nodejs]:https://nodejs.org/en/download/
[ruby-gems]:https://rubygems.org/pages/download
